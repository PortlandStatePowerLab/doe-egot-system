#include "include/wadl/wadl.hpp"
#include <utilities/utilities.hpp>
#include <xml/utilities.hpp>
#include <boost/foreach.hpp>
#include <iostream>

static std::unordered_map <std::string, std::string> uri_map = 
{
    {"DeviceCapability", "/dcap"},
    {"SelfDevice", "/sdev"},
    {"EndDevice", "/edev"},
    {"Registration", "/rg"},
    {"DeviceStatus", "/dstat"},
    {"FunctionSetAssignments", "/fsa"},
    {"Subscription", "/sub"},
    {"Notification", "/ntfy"},
    {"ResponseSet", "/rsps"},
    {"Response", "/rsp"},
    {"Time", "/tm"},
    {"DeviceInformation", "/di"},
    {"SupportedLocale", "/loc"},
    {"PowerStatus", "/ps"},
    {"IPAddr", "/addr"},
    {"RPLInstance", "/rpl"},
    {"LLInterface", "/ll"},
    {"Neighbor", "/nbh"},
    {"LogEvent", "/lel"},
    {"Configuration", "/cfg"},
    {"PriceResponseCfg", "/prcfg"},
    {"File", "/file"},
    {"FileStatus", "/fs"},
    {"ActiveEndDeviceControl", "/actedc"},
    {"EndDeviceControl", "/edc"},
    {"LoadShedAvailability", "/lsl"},
    {"UsagePoint", "/upt"},
    {"MeterReading", "/mr"},
    {"ReadingType", "/rt"},
    {"ReadingSet", "/rs"},
    {"Reading", "/r"},
    {"MirrorUsagePoint", "/mup"},
    {"TariffProfile", "/tp"},
    {"RateComponent", "/rc"},
    {"ActiveTimeTariffInterval","/acttti"},
    {"TimeTariffInterval", "/tti"},
    {"ConsumptionTariffInterval", "/cti"},
    {"MessagingProgram", "/msg"},
    {"ActiveTextMessage", "/acttxt"},
    {"TextMessage", "/txt"},
    {"CustomerAccount", "/bill"},
    {"CustomerAgreement", "/ca"},
    {"ActiveBillingPeriod", "/actbp"},
    {"BillingPeriod", "/bp"},
    {"ProjectionReading", "/pro"},
    {"BillingReadingSet", "/brs"},
    {"BillingReading", "/br"},
    {"TargetReading", "/tar"},
    {"HistoricalReading", "/ver"},
    {"ServiceSupplier", "/ss"},
    {"Prepayment", "/ppy"},
    {"AccountBalance", "/ab"},
    {"PrepayOperationStatus", "/os"},
    {"ActiveSupplyInterruptionOverride","/actsi"},
    {"SupplyInterruptionOverride", "/si"},
    {"CreditRegister", "/cr"},
    {"FlowReservationRequest", "/frq"},
    {"FlowReservationResponse", "/frp"},
    {"DER", "/der"},
    {"AssociatedUsagePoint", "/aupt"},
    {"DERProgram", "/derp"},
    {"CurrentDERProgram", "/cdp"},
    {"DERSettings", "/derg"},
    {"DERStatus", "/ders"},
    {"DERAvailability", "/dera"},
    {"DERCapability", "/dercap"},
    {"ActiveDERControlList", "/actderc"},
    {"DERControl", "/derc"},
    {"DefaultDERControl", "/dderc"},
    {"DERCurve", "/dc"}
};

// Using boost::beast verb enums this bitset will create a bit mask that can be used
// to determine if the request method is acceptable.
void bitSet(boost::property_tree::ptree::value_type& tree, std::unordered_map<std::string, uint16_t> *wadl)
{
    std::string key = "";
    uint16_t result;
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
                result += 1 << 2;
            }

            if (method == "HEAD" && (mode == "M" || mode == "O"))
            {
                result += 1 << 3;
            }

            if (method == "PUT" && (mode == "M" || mode == "O"))
            {
                result += 1 << 5;
            }

            if (method == "POST" && (mode == "M" || mode == "O"))
            {
                result += 1 << 4;
            }

            if (method == "DELETE" && (mode == "M" || mode == "O"))
            {
                result += 1 << 1;
            }
        }
    };

    if (!key.empty())
    {
        wadl->emplace(key, result);
    }
};

void loadWADL(const std::string &wadl_path, std::unordered_map<std::string, uint16_t> *wadl)
{
    std::string wadl_file = psu::utilities::readFile(wadl_path);
    boost::property_tree::ptree pt = xml::util::Treeify(wadl_file);

    BOOST_FOREACH (boost::property_tree::ptree::value_type &tree, pt.get_child("application.resources"))
    {
        if (tree.first == "resource")
        {
            bitSet(tree, wadl);
        }
    };

    for (const auto& ele : *wadl)
    {
        std::cout << ele.first << " : " << ele.second << "\n";
    }
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

    uint16_t WADL::getAccess(const std::string& uri)
    {
        uint16_t value = wadl_.count(uri);
        if (value == 0)
        {
            return value;
        }
        return wadl_.at(uri);
    }
} // namespace sep


