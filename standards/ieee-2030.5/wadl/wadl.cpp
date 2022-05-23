#include "include/wadl/wadl.hpp"
#include <utilities/utilities.hpp>
#include <xml/utilities.hpp>
#include <boost/foreach.hpp>
#include <iostream>

static std::unordered_map <std::string, std::string> uri_map = 
{
    {"DeviceCapability", "/dcap"},
    {"SelfDevice", "/sdev/*"},
    {"EndDeviceList", "/edev"},
    {"EndDevice", "/edev/*"},
    {"Registration", "/rg"},
    {"DeviceStatus", "/dstat"},
    {"FunctionSetAssignmentsList", "/fsa"},
    {"FunctionSetAssignments", "/fsa/*"},
    {"SubscriptionList", "/sub"},
    {"Subscription", "/sub/*"},
    {"NotificationList", "/ntfy"},
    {"Notification", "/ntfy/*"},
    {"ResponseSetList", "/rsps"},
    {"ResponseSet", "/rsps/*"},
    {"ResponseList", "/rsp"},
    {"Response", "/rsp/*"},
    {"Time", "/tm"},
    {"DeviceInformation", "/di"},
    {"SupportedLocaleList", "/loc"},
    {"SupportedLocale", "/loc/*"},
    {"PowerStatus", "/ps"},
    {"IPInterfaceList", "/ns"},
    {"IPInterface", "/ns/*"},
    {"IPAddrList", "/addr"},
    {"IPAddr", "/addr/*"},
    {"RPLInstanceList", "/rpl"},
    {"RPLInstance", "/rpl/*"},
    {"RPLSourceRoutesList", "/srt"},
    {"RPLSourceRoutes", "/srt/*"},
    {"LLInterfaceList", "/ll"},
    {"LLInterface", "/ll/*"},
    {"NeighborList", "/nbh"},
    {"Neighbor", "/nbh/*"},
    {"LogEventList", "/lel"},
    {"LogEvent", "/lel/*"},
    {"Configuration", "/cfg"},
    {"PriceResponseCfgList", "/prcfg"},
    {"PriceResponseCfg", "/prcfg/*"},
    {"FileList", "/file"},
    {"File", "/file/*"},
    {"FileStatus", "/fs"},
    {"DemandResponseProgramList", "/dr"},
    {"DemandResponseProgram", "/dr/*"},
    {"ActiveEndDeviceControlList", "/actedc"},
    {"ActiveEndDeviceControl", "/actedc/*"},
    {"EndDeviceControlList", "/edc"},
    {"EndDeviceControl", "/edc/*"},
    {"LoadShedAvailabilityList", "/lsl"},
    {"LoadShedAvailability", "/lsl/*"},
    {"UsagePointList", "/upt"},
    {"UsagePoint", "/upt/*"},
    {"MeterReadingList", "/mr"},
    {"MeterReading", "/mr/*"},
    {"ReadingType", "/rt"},
    {"ReadingSetList", "/rs"},
    {"ReadingSet", "/rs/*"},
    {"ReadingList", "/r"},
    {"Reading", "/r/*"},
    {"MirrorUsagePointList", "/mup"},
    {"MirrorUsagePoint", "/mup/*"},
    {"TariffProfileList", "/tp"},
    {"TariffProfile", "/tp/*"},
    {"RateComponentList", "/rc"},
    {"RateComponent", "/rc/*"},
    {"ActiveTimeTariffIntervalList","/acttti"},
    {"TimeTariffIntervalList", "/tti"},
    {"TimeTariffInterval", "/tti/*"},
    {"ConsumptionTariffIntervalList", "/cti"},
    {"ConsumptionTariffInterval", "/cti/*"},
    {"MessagingProgramList", "/msg"},
    {"MessagingProgram", "/msg/*"},
    {"ActiveTextMessageList", "/acttxt"},
    {"TextMessageList", "/txt"},
    {"TextMessage", "/txt/*"},
    {"CustomerAccountList", "/bill"},
    {"CustomerAccount", "/bill/*"},
    {"CustomerAgreementList", "/ca"},
    {"CustomerAgreement", "/ca/*"},
    {"ActiveBillingPeriodList", "/actbp"},
    {"BillingPeriodList", "/bp"},
    {"BillingPeriod", "/bp/*"},
    {"ProjectionReadingList", "/pro"},
    {"ProjectionReading", "/pro/*"},
    {"BillingReadingSetList", "/brs"},
    {"BillingReadingSet", "/brs/*"},
    {"BillingReadingList", "/br"},
    {"BillingReading", "/br/*"},
    {"TargetReadingList", "/tar"},
    {"TargetReading", "/tar/*"},
    {"HistoricalReadingList", "/ver"},
    {"HistoricalReading", "/ver/*"},
    {"ServiceSupplier", "/ss"},
    {"PrepaymentList", "/ppy"},
    {"Prepayment", "/ppy/*"},
    {"AccountBalance", "/ab"},
    {"PrepayOperationStatus", "/os"},
    {"ActiveSupplyInterruptionOverrideList","/actsi"},
    {"SupplyInterruptionOverrideList", "/si"},
    {"SupplyInterruptionOverride", "/si/*"},
    {"CreditRegisterList", "/cr"},
    {"CreditRegister", "/cr/*"},
    {"FlowReservationRequestList", "/frq"},
    {"FlowReservationRequest", "/frq/*"},
    {"FlowReservationResponseList", "/frp"},
    {"FlowReservationResponse", "/frp/*"},
    {"DERList", "/der"},
    {"DER", "/der/*"},
    {"AssociatedUsagePointList", "/aupt"},
    {"DERProgramList", "/derp"},
    {"DERProgram", "/derp/*"},
    {"CurrentDERProgram", "/cdp"},
    {"DERSettings", "/derg"},
    {"DERStatus", "/ders"},
    {"DERAvailability", "/dera"},
    {"DERCapability", "/dercap"},
    {"ActiveDERControlList", "/actderc"},
    {"DERControlList", "/derc"},
    {"DERControl", "/derc/*"},
    {"DefaultDERControl", "/dderc"},
    {"DERCurveList", "/dc"},
    {"DERCurve", "/dc/*"}
};

// pass the wadl "resource" and go through each method
void recursiveMethod(
    const boost::property_tree::ptree& tree, 
    const std::string &name, 
    const std::string &tag, 
    sep::WADLResource *wadl)
{
    if (tree.empty())
    {
        if (tag == "mediaType")
        {
            wadl->properties[name].content_type.emplace_back(tree.data());
        }
        else if (tag == "status")
        {
            wadl->properties[name].status.emplace_back(std::stol(tree.data()));
        }
        else if (tag == "params")
        {
            wadl->properties[name].params.emplace_back(tree.data());
        }
    }
    else
    {
        for (const auto it : tree)
        {
            recursiveMethod(it.second, name, it.first, wadl);
        }
    }
    return;    
};

// Using boost::beast verb enums this bitset will create a bit mask that can be used
// to determine if the request method is acceptable.
void propSet(boost::property_tree::ptree::value_type& tree, std::unordered_map<std::string, sep::WADLResource> *wadl)
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

            resource.properties[method].allow = (mode == "M") || (mode == "O");
            if (resource.properties[method].allow)
            {
                recursiveMethod(subtree.second, method, "", &resource);
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

    BOOST_FOREACH (boost::property_tree::ptree::value_type &tree, pt.get_child("application.resources"))
    {
        if (tree.first == "resource")
        {
            propSet(tree, wadl);
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
            return wadl_[uri];
        }
        return WADLResource();
    }
} // namespace sep


