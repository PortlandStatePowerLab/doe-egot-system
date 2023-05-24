#include <sep/xml/device_capability_adapter.hpp>
#include <sep/xml/utilities.hpp>
#include <sep/models/simple_types.hpp>
#include <boost/optional.hpp>

namespace xml
{
    void ObjectMap(const boost::property_tree::ptree &pt, sep::DeviceCapability *dcap)
    {
        std::string path = "DeviceCapability.<xmlattr>.href";
        dcap->href =  pt.get<std::string>(path);

        path = "DeviceCapability.<xmlattr>.pollRate";
        dcap->poll_rate= pt.get<sep::UInt32>(path);

        path = "DeviceCapability.CustomerAccountListLink.<xmlattr>.href";
        if(auto href = pt.get_optional<std::string>(path)){
            dcap->customer_account_list_link.value().href = href.value();
        }
        path = "DeviceCapability.CustomerAccountListLink.<xmlattr>.href";
        if(auto all = pt.get_optional<sep::UInt32>(path)){
            dcap->customer_account_list_link.value().all = all.value();
        }
        path = "DeviceCapability.DemandResponseProgramListLink.<xmlattr>.href";
        if(auto href = pt.get_optional<std::string>(path)){
            dcap->demand_response_program_list_link.value().href = href.value();
        }
        path = "DeviceCapability.DemandResponseProgramListLink.<xmlattr>.all";
        if(auto all = pt.get_optional<sep::UInt32>(path)){
            dcap->demand_response_program_list_link.value().all = all.value();
        }
        path = "DeviceCapability.DERProgramListLink.<xmlattr>.href";
        if(auto href = pt.get_optional<std::string>(path)){
            dcap->der_program_list_link.value().href = href.value();
        }
        path = "DeviceCapability.DERProgramListLink.<xmlattr>.all";
        if(auto all = pt.get_optional<sep::UInt32>(path)){
            dcap->der_program_list_link.value().all = all.value();
        }
        path = "DeviceCapability.FileListLink.<xmlattr>.href";
        if(auto href = pt.get_optional<std::string>(path)){
            dcap->file_list_link.value().href = href.value();
        }
        path = "DeviceCapability.FileListLink.<xmlattr>.all";
        if(auto all = pt.get_optional<sep::UInt32>(path)){
            dcap->file_list_link.value().all = all.value();
        }
        path = "DeviceCapability.MessagingProgramListLink.<xmlattr>.href";
        if(auto href = pt.get_optional<std::string>(path)){
            dcap->messaging_program_list_link.value().href = href.value();
        }
        path = "DeviceCapability.MessagingProgramListLink.<xmlattr>.all";
        if(auto all = pt.get_optional<sep::UInt32>(path)){
            dcap->messaging_program_list_link.value().all = all.value();
        }
        path = "DeviceCapability.PrepaymentListLink.<xmlattr>.href";
        if(auto href = pt.get_optional<std::string>(path)){
            dcap->prepayment_list_link.value().href = href.value();
        }
        path = "DeviceCapability.PrepaymentListLink.<xmlattr>.all";
        if(auto all = pt.get_optional<sep::UInt32>(path)){
            dcap->prepayment_list_link.value().all = all.value();
        }
        path = "DeviceCapability.ResponseSetListLink.<xmlattr>.href";
        if(auto href = pt.get_optional<std::string>(path)){
            dcap->response_set_list_link.value().href = href.value();
        }
        path = "DeviceCapability.ResponseSetListLink.<xmlattr>.all";
        if(auto all = pt.get_optional<sep::UInt32>(path)){
            dcap->response_set_list_link.value().all = all.value();
        }
        path = "DeviceCapability.TariffProfileListLink.<xmlattr>.href";
        if(auto href = pt.get_optional<std::string>(path)){
            dcap->tariff_profile_list_link.value().href = href.value();
        }
        path = "DeviceCapability.TariffProfileListLink.<xmlattr>.all";
        if(auto all = pt.get_optional<sep::UInt32>(path)){
            dcap->tariff_profile_list_link.value().all = all.value();
        }
        path = "DeviceCapability.TimeLink.<xmlattr>.href";
        if(auto href = pt.get_optional<std::string>(path)){
            dcap->time_link.value().href = href.value();
        }
        path = "DeviceCapability.UsagePointListLink.<xmlattr>.href";
        if(auto href = pt.get_optional<std::string>(path)){
            dcap->usage_point_list_link.value().href = href.value();
        }
        path = "DeviceCapability.UsagePointListLink.<xmlattr>.all";
        if(auto all = pt.get_optional<sep::UInt32>(path)){
            dcap->usage_point_list_link.value().all = all.value();
        }
        path = "DeviceCapability.EndDeviceListLink.<xmlattr>.href";
        if(auto href = pt.get_optional<std::string>(path)){
            dcap->end_device_list_link.value().href = href.value();
        }
        path = "DeviceCapability.EndDeviceListLink.<xmlattr>.all";
        if(auto all = pt.get_optional<sep::UInt32>(path)){
            dcap->end_device_list_link.value().all = all.value();
        }
        path = "DeviceCapability.MirrorUsagePointListLink.<xmlattr>.href";
        if(auto href = pt.get_optional<std::string>(path)){
            dcap->mirror_usage_point_list_link.value().href = href.value();
        }
        path = "DeviceCapability.MirrorUsagePointListLink.<xmlattr>.all";
        if(auto all = pt.get_optional<sep::UInt32>(path)){
            dcap->mirror_usage_point_list_link.value().all = all.value();
        }
        path = "DeviceCapability.SelfDeviceLink.<xmlattr>.href";
        if(auto href = pt.get_optional<std::string>(path)){
            dcap->self_device_link.value().href = href.value();
        }
    };

    void TreeMap(const sep::DeviceCapability &dcap, boost::property_tree::ptree *pt)
    {
        std::string path = "DeviceCapability.<xmlattr>.href";
        pt->put(path, dcap.href);
        path = "DeviFunctionSetAssignmentsBaseceCapability.<xmlattr>.pollRate";
        pt->put(path, dcap.poll_rate);
        if(dcap.customer_account_list_link.has_value()){
            path = "DeviceCapability.CustomerAccountListLink.<xmlattr>.href";
            pt->put(path, dcap.customer_account_list_link.value().href);
            path = "DeviceCapability.CustomerAccountListLink.<xmlattr>.all";
            pt->put(path, dcap.customer_account_list_link.value().all);
        }
        if(dcap.demand_response_program_list_link.has_value()){
            path = "DeviceCapability.DemandResponseProgramListLink.<xmlattr>.href";
            pt->put(path, dcap.demand_response_program_list_link.value().href);
            path = "DeviceCapability.DemandResponseProgramListLink.<xmlattr>.all";
            pt->put(path, dcap.demand_response_program_list_link.value().all);
        }
        if(dcap.der_program_list_link.has_value()){
            path = "DeviceCapability.DERProgramListLink.<xmlattr>.href";
            pt->put(path, dcap.der_program_list_link.value().href);
            path = "DeviceCapability.DERProgramListLink.<xmlattr>.all";
            pt->put(path, dcap.der_program_list_link.value().all);
        }
        if(dcap.file_list_link.has_value()){
            path = "DeviceCapability.FileListLink.<xmlattr>.href";
            pt->put(path, dcap.file_list_link.value().href);
            path = "DeviceCapability.FileListLink.<xmlattr>.all";
            pt->put(path, dcap.file_list_link.value().all);
        }
        if(dcap.messaging_program_list_link.has_value()){
            path = "DeviceCapability.MessagingProgramListLink.<xmlattr>";
            pt->put(path, dcap.messaging_program_list_link.value().href);
            path = "DeviceCapability.MessagingProgramListLink.<xmlattr>.all";
            pt->put(path, dcap.messaging_program_list_link.value().all);
        }
        if(dcap.prepayment_list_link.has_value()){
            path = "DeviceCapability.PrepaymentListLink.<xmlattr>.href";
            pt->put(path, dcap.prepayment_list_link.value().href);
            path = "DeviceCapability.PrepaymentListLink.<xmlattr>.all";
            pt->put(path, dcap.prepayment_list_link.value().all);
        }
        if(dcap.response_set_list_link.has_value()){
            path = "DeviceCapability.ResponseSetListLink.<xmlattr>.href";
            pt->put(path, dcap.response_set_list_link.value().href);
            path = "DeviceCapability.ResponseSetListLink.<xmlattr>.all";
            pt->put(path, dcap.response_set_list_link.value().all);
        }
        if(dcap.tariff_profile_list_link.has_value()){
            path = "DeviceCapability.TariffProfileListLink.<xmlattr>.href";
            pt->put(path, dcap.tariff_profile_list_link.value().href);
            path = "DeviceCapability.TariffProfileListLink.<xmlattr>.all";
            pt->put(path, dcap.tariff_profile_list_link.value().all);
        }
        if(dcap.time_link.has_value()){
            path = "DeviceCapability.TimeLink.<xmlattr>.href";
            pt->put(path, dcap.time_link.value().href);
        }
        if(dcap.usage_point_list_link.has_value()){
            path = "DeviceCapability.UsagePointListLink.<xmlattr>.href";
            pt->put(path, dcap.usage_point_list_link.value().href);
            path = "DeviceCapability.UsagePointListLink.<xmlattr>.all";
            pt->put(path, dcap.usage_point_list_link.value().all);
        }
        if(dcap.end_device_list_link.has_value()){
            path = "DeviceCapability.EndDeviceListLink.<xmlattr>.href";
            pt->put(path, dcap.end_device_list_link.value().href);
            path = "DeviceCapability.EndDeviceListLink.<xmlattr>.all";
            pt->put(path, dcap.end_device_list_link.value().all);
        }
        if(dcap.mirror_usage_point_list_link.has_value()){
            path = "DeviceCapability.MirrorUsagePointListLink.<xmlattr>.href";
            pt->put(path, dcap.mirror_usage_point_list_link.value().href);
            path = "DeviceCapability.MirrorUsagePointListLink.<xmlattr>.all";
            pt->put(path, dcap.mirror_usage_point_list_link.value().all);
        }
        if(dcap.self_device_link.has_value()){
            path = "DeviceCapability.SelfDeviceLink.<xmlattr>.href";
            pt->put(path, dcap.self_device_link.value().href);
        }
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
