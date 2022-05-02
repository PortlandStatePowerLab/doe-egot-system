#include "include/wadl/wadl.hpp"
#include <utilities/utilities.hpp>
#include <xml/utilities.hpp>
#include <boost/foreach.hpp>
#include <iostream>

static std::unordered_map <std::string, std::string> uri_map = 
{
    {"DeviceCapability", "/dcap"},
    {"SelfDevice", "/sdev"},
    {"EndDeviceList", "/edev"},
    {"Registration", "/rg"},
    {"DeviceStatus", "/dstat"},
    {"FunctionSetAssignmentsList", "/fsa"},
    {"SubscriptionList", "/sub"},
    {"NotificationList", "/ntfy"},
    {"ResponseSetList", "/rsps"},
    {"ResponseList", "/rsp"},
    {"Time", "/tm"},
    {"DeviceInformation", "/di"},
    {"SupportedLocaleList", "/loc"},
    {"PowerStatus", "/ps"},
    {"IPInterfaceList", "/ns"},
    {"IPAddrList", "/addr"},
    {"RPLInstanceList", "/rpl"},
    {"RPLSourceRoutesList", "/srt"},
    {"LLInterfaceList", "/ll"},
    {"NeighborList", "/nbh"},
    {"LogEventList", "/lel"},
    {"Configuration", "/cfg"},
    {"PriceResponseCfgList", "/prcfg"},
    {"FileList", "/file"},
    {"FileStatus", "/fs"},
    {"DemandResponseProgramList", "/dr"},
    {"ActiveEndDeviceControlList", "/actedc"},
    {"EndDeviceControlList", "/edc"},
    {"LoadShedAvailabilityList", "/lsl"},
    {"UsagePointList", "/upt"},
    {"MeterReadingList", "/mr"},
    {"ReadingType", "/rt"},
    {"ReadingSetList", "/rs"},
    {"ReadingList", "/r"},
    {"MirrorUsagePointList", "/mup"},
    {"TariffProfileList", "/tp"},
    {"RateComponentList", "/rc"},
    {"ActiveTimeTariffIntervalList","/acttti"},
    {"TimeTariffIntervalList", "/tti"},
    {"ConsumptionTariffIntervalList", "/cti"},
    {"MessagingProgramList", "/msg"},
    {"ActiveTextMessageList", "/acttxt"},
    {"TextMessageList", "/txt"},
    {"CustomerAccountList", "/bill"},
    {"CustomerAgreementList", "/ca"},
    {"ActiveBillingPeriodList", "/actbp"},
    {"BillingPeriodList", "/bp"},
    {"ProjectionReadingList", "/pro"},
    {"BillingReadingSetList", "/brs"},
    {"BillingReadingList", "/br"},
    {"TargetReadingList", "/tar"},
    {"HistoricalReadingList", "/ver"},
    {"ServiceSupplier", "/ss"},
    {"PrepaymentList", "/ppy"},
    {"AccountBalance", "/ab"},
    {"PrepayOperationStatus", "/os"},
    {"ActiveSupplyInterruptionOverrideList","/actsi"},
    {"SupplyInterruptionOverrideList", "/si"},
    {"CreditRegisterList", "/cr"},
    {"FlowReservationRequestList", "/frq"},
    {"FlowReservationResponseList", "/frp"},
    {"DERList", "/der"},
    {"AssociatedUsagePointList", "/aupt"},
    {"DERProgramList", "/derp"},
    {"CurrentDERProgram", "/cdp"},
    {"DERSettings", "/derg"},
    {"DERStatus", "/ders"},
    {"DERAvailability", "/dera"},
    {"DERCapability", "/dercap"},
    {"ActiveDERControlList", "/actderc"},
    {"DERControlList", "/derc"},
    {"DefaultDERControl", "/dderc"},
    {"DERCurveList", "/dc"}
};

void recursiveTree(const boost::property_tree::ptree& tree, const std::string &tag, int level)
{
    if (tree.empty())
    {
        std::cout << tag << " : " << tree.data() << std::endl;
    }
    else
    {
        for (const auto it : tree)
        {
            recursiveTree(it.second, it.first, level++);
        }
    }
    return;    
};

// Using boost::beast verb enums this bitset will create a bit mask that can be used
// to determine if the request method is acceptable.
void bitSet(boost::property_tree::ptree::value_type& tree, std::unordered_map<std::string, sep::WADLResource> *wadl)
{
    std::string key = "";
    sep::WADLResource resource;
    bool skip = false;
    BOOST_FOREACH (boost::property_tree::ptree::value_type &subtree, tree.second.get_child(""))
    {
        if (subtree.first == "<xmlattr>")
        {
            if (uri_map.count(subtree.second.get<std::string>("id")) == 0)
            {
                skip = true;
            }
            else
            {
                skip = false;
                key = uri_map.at(subtree.second.get<std::string>("id"));
            }
        }
        if (subtree.first == "method" && !skip)
        {
            std::string method = subtree.second.get<std::string>("<xmlattr>.name");
            std::string mode = subtree.second.get<std::string>("<xmlattr>.wx:mode");

            if (method == "GET" && (mode == "M" || mode == "O"))
            {
                std::string content_type = subtree.second.get<std::string>("<xmlattr>.wx:mode", "");
                resource.methods_bit_mask += 1 << 2;
            }

            if (method == "HEAD" && (mode == "M" || mode == "O"))
            {
                resource.methods_bit_mask += 1 << 3;
            }

            if (method == "PUT" && (mode == "M" || mode == "O"))
            {
                resource.methods_bit_mask += 1 << 5;
            }

            if (method == "POST" && (mode == "M" || mode == "O"))
            {
                resource.methods_bit_mask += 1 << 4;
            }

            if (method == "DELETE" && (mode == "M" || mode == "O"))
            {
                resource.methods_bit_mask += 1 << 1;
            }
        }
    };

    if (!key.empty())
    {
        wadl->emplace(key, resource);
    }
};

void loadWADL(const std::string &wadl_path, std::unordered_map<std::string, sep::WADLResource> *wadl)
{
    std::string wadl_file = psu::utilities::readFile(wadl_path);
    boost::property_tree::ptree pt = xml::util::Treeify(wadl_file);

    recursiveTree(pt, "", 1);

    BOOST_FOREACH (boost::property_tree::ptree::value_type &tree, pt.get_child("application.resources"))
    {
        if (tree.first == "resource")
        {
            bitSet(tree, wadl);
        }
    };
};

namespace sep
{
    WADL* WADL::instance_{nullptr};
    std::mutex WADL::mutex_;

    WADL::WADL (const std::string& wadl_path)
    {
        loadWADL(wadl_path, &wadl_);
    }

    WADL::~WADL()
    {
        delete instance_;
    }

    WADL* WADL::getInstance(const std::string& wadl_path)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (instance_ == nullptr)
        {
            instance_ = new WADL(wadl_path);
        }
        return instance_;
    }

    WADLResource WADL::getResource(const std::string& uri)
    {
        if (wadl_.count(uri) > 0)
        {
            return wadl_.at(uri);
        }
        return WADLResource();
    }
} // namespace sep


