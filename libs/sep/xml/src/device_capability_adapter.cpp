#include <sep/xml/device_capability_adapter.hpp>
#include <sep/xml/utilities.hpp>
#include <sep/models/simple_types.hpp>
#include <boost/optional.hpp>

namespace xml
{
    void ObjectMap(const boost::property_tree::ptree &pt, sep::DeviceCapability *dcap)
    {

        if(boost::optional<sep::UInt32> poll_rate = pt.get_optional<sep::UInt32>("DeviceCapability.<xmlattr>.pollRate")){
            dcap->poll_rate = poll_rate.get();
        }
         
        if(boost::optional<std::string> href = pt.get_optional<std::string>("DeviceCapability.<xmlattr>.href")){
            dcap->href = href.get();
        }

        if(boost::optional<std::string> href = pt.get<std::string>("DeviceCapability.CustomerAccountListLink.<xmlattr>.href")){
            dcap->customer_account_list_link.href = href.get();
        }

        if(boost::optional<sep::UInt32> all = pt.get<sep::UInt32>("DeviceCapability.CustomerAccountListLink.<xmlattr>.all")){
            dcap->customer_account_list_link.all = all.get();
        }
        
        dcap->demand_response_program_list_link.href = pt.get<std::string>("DeviceCapability.DemandResponseProgramListLink.<xmlattr>.href", "");
        dcap->demand_response_program_list_link.all = pt.get<uint32_t>("DeviceCapability.DemandResponseProgramListLink.<xmlattr>.all", 0);
        dcap->der_program_list_link.href = pt.get<std::string>("DeviceCapability.DERProgramListLink.<xmlattr>.href", "");
        dcap->der_program_list_link.all = pt.get<uint32_t>("DeviceCapability.DERProgramListLink.<xmlattr>.all", 0);
        dcap->file_list_link.href = pt.get<std::string>("DeviceCapability.FileListLink.<xmlattr>.href", "");
        dcap->file_list_link.all = pt.get<uint32_t>("DeviceCapability.FileListLink.<xmlattr>.all", 0);
        dcap->messaging_program_list_link.href = pt.get<std::string>("DeviceCapability.MessagingProgramListLink.<xmlattr>.href", "");
        dcap->messaging_program_list_link.all = pt.get<uint32_t>("DeviceCapability.MessagingProgramListLink.<xmlattr>.all", 0);
        dcap->prepayment_list_link.href = pt.get<std::string>("DeviceCapability.PrepaymentListLink.<xmlattr>.href", "");
        dcap->prepayment_list_link.all = pt.get<uint32_t>("DeviceCapability.PrepaymentListLink.<xmlattr>.all", 0);
        dcap->response_set_list_link.href = pt.get<std::string>("DeviceCapability.ResponseSetListLink.<xmlattr>.href", "");
        dcap->response_set_list_link.all = pt.get<uint32_t>("DeviceCapability.ResponseSetListLink.<xmlattr>.all", 0);
        dcap->tariff_profile_list_link.href = pt.get<std::string>("DeviceCapability.TariffProfileListLink.<xmlattr>.href", "");
        dcap->tariff_profile_list_link.all = pt.get<uint32_t>("DeviceCapability.TariffProfileListLink.<xmlattr>.all", 0);
        dcap->time_link.href = pt.get<std::string>("DeviceCapability.TimeLink.<xmlattr>.href", "");
        dcap->usage_point_list_link.href = pt.get<std::string>("DeviceCapability.UsagePointListLink.<xmlattr>.href", "");
        dcap->usage_point_list_link.all = pt.get<uint32_t>("DeviceCapability.UsagePointListLink.<xmlattr>.all", 0);
        dcap->end_device_list_link.href = pt.get<std::string>("DeviceCapability.EndDeviceListLink.<xmlattr>.href", "");
        dcap->end_device_list_link.all = pt.get<uint32_t>("DeviceCapability.EndDeviceListLink.<xmlattr>.all", 0);
        dcap->mirror_usage_point_list_link.href = pt.get<std::string>("DeviceCapability.MirrorUsagePointListLink.<xmlattr>.href", "");
        dcap->mirror_usage_point_list_link.all = pt.get<uint32_t>("DeviceCapability.MirrorUsagePointListLink.<xmlattr>.all", 0);
        dcap->self_device_link.href = pt.get<std::string>("DeviceCapability.SelfDeviceLink.<xmlattr>.href", "");
    };

    void TreeMap(const sep::DeviceCapability &dcap, boost::property_tree::ptree *pt)
    {
        pt->put("DeviceCapability.<xmlattr>.pollRate", dcap.poll_rate);
        pt->put("DeviceCapability.<xmlattr>.href", dcap.href);
        pt->put("DeviceCapability.CustomerAccountListLink.<xmlattr>.href", dcap.customer_account_list_link.href);
        pt->put("DeviceCapability.CustomerAccountListLink.<xmlattr>.all", dcap.customer_account_list_link.all);
        pt->put("DeviceCapability.DemandResponseProgramListLink.<xmlattr>.href", dcap.demand_response_program_list_link.href);
        pt->put("DeviceCapability.DemandResponseProgramListLink.<xmlattr>.all", dcap.demand_response_program_list_link.all);
        pt->put("DeviceCapability.DERProgramListLink.<xmlattr>.href", dcap.der_program_list_link.href);
        pt->put("DeviceCapability.DERProgramListLink.<xmlattr>.all", dcap.der_program_list_link.all);
        pt->put("DeviceCapability.FileListLink.<xmlattr>.href", dcap.file_list_link.href);
        pt->put("DeviceCapability.FileListLink.<xmlattr>.all", dcap.file_list_link.all);
        pt->put("DeviceCapability.MessagingProgramListLink.<xmlattr>.href", dcap.messaging_program_list_link.href);
        pt->put("DeviceCapability.MessagingProgramListLink.<xmlattr>.all", dcap.messaging_program_list_link.all);
        pt->put("DeviceCapability.PrepaymentListLink.<xmlattr>.href", dcap.prepayment_list_link.href);
        pt->put("DeviceCapability.PrepaymentListLink.<xmlattr>.all", dcap.prepayment_list_link.all);
        pt->put("DeviceCapability.ResponseSetListLink.<xmlattr>.href", dcap.response_set_list_link.href);
        pt->put("DeviceCapability.ResponseSetListLink.<xmlattr>.all", dcap.response_set_list_link.all);
        pt->put("DeviceCapability.TariffProfileListLink.<xmlattr>.href", dcap.tariff_profile_list_link.href);
        pt->put("DeviceCapability.TariffProfileListLink.<xmlattr>.all", dcap.tariff_profile_list_link.all);
        pt->put("DeviceCapability.TimeLink.<xmlattr>.href", dcap.time_link.href);
        pt->put("DeviceCapability.UsagePointListLink.<xmlattr>.href", dcap.usage_point_list_link.href);
        pt->put("DeviceCapability.UsagePointListLink.<xmlattr>.all", dcap.usage_point_list_link.all);
        pt->put("DeviceCapability.EndDeviceListLink.<xmlattr>.href", dcap.end_device_list_link.href);
        pt->put("DeviceCapability.EndDeviceListLink.<xmlattr>.all", dcap.end_device_list_link.all);
        pt->put("DeviceCapability.MirrorUsagePointListLink.<xmlattr>.href", dcap.mirror_usage_point_list_link.href);
        pt->put("DeviceCapability.MirrorUsagePointListLink.<xmlattr>.all", dcap.mirror_usage_point_list_link.all);
        pt->put("DeviceCapability.SelfDeviceLink.<xmlattr>.href", dcap.self_device_link.href);
    };

    std::string Serialize(const sep::DeviceCapability &dcap)
    {
        boost::property_tree::ptree pt;
        TreeMap(dcap, &pt);

        xml::util::SetSchema(&pt);
        return xml::util::Stringify(&pt);
    }

    void Parse(const std::string &xml_str, sep::DeviceCapability *dcap)
    {
        boost::property_tree::ptree pt = xml::util::Treeify(xml_str);
        ObjectMap(pt, dcap);
    }
} // namespace xml
