#include <sep/xml/device_capability_adapter.hpp>
#include <sep/xml/utilities.hpp>
#include <sep/models/simple_types.hpp>
#include <boost/optional.hpp>

namespace xml
{
    void ObjectMap(const boost::property_tree::ptree &pt, sep::DeviceCapability *dcap)
    {
        std::string path = "deviceCapability.<xmlattr>.href";
        dcap->href =  pt.get<std::string>(path);

        path = "deviceCapability.<xmlattr>.pollRate";
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
        path = "DeviceCapability.CustomerAccountListLink.<xmlattr>";
        if(dcap.customer_account_list_link.href != ""){
            pt->put(path+".href", dcap.customer_account_list_link.href);
            pt->put(path+".all", dcap.customer_account_list_link.all);
        }
        path = "DeviceCapability.DemandResponseProgramListLink.<xmlattr>";
        if(dcap.demand_response_program_list_link.href != ""){
            pt->put(path+".href", dcap.demand_response_program_list_link.href);
            pt->put(path+".all", dcap.demand_response_program_list_link.all);
        }
        path = "DeviceCapability.DERProgramListLink.<xmlattr>";
        if(dcap.der_program_list_link.href != ""){
            pt->put(path+".href", dcap.der_program_list_link.href);
            pt->put(path+".all", dcap.der_program_list_link.all);
        }
        path = "DeviceCapability.FileListLink.<xmlattr>";
        if(dcap.file_list_link.href != ""){
            pt->put(path+".href", dcap.file_list_link.href);
            pt->put(path+".all", dcap.file_list_link.all);
        }
        path = "DeviceCapability.MessagingProgramListLink.<xmlattr>";
        if(dcap.messaging_program_list_link.href != ""){
            pt->put(path+".href", dcap.messaging_program_list_link.href);
            pt->put(path+".all", dcap.messaging_program_list_link.all);
        }
        path = "DeviceCapability.PrepaymentListLink.<xmlattr>";
        if(dcap.prepayment_list_link.href != ""){
            pt->put(path+".href", dcap.prepayment_list_link.href);
            pt->put(path+".all", dcap.prepayment_list_link.all);
        }
        path = "DeviceCapability.ResponseSetListLink.<xmlattr>";
        if(dcap.response_set_list_link.href != ""){
            pt->put(path+".href", dcap.response_set_list_link.href);
            pt->put(path+".all", dcap.response_set_list_link.all);
        }
        path = "DeviceCapability.TariffProfileListLink.<xmlattr>";
        if(dcap.tariff_profile_list_link.href != ""){
            pt->put(path+".href", dcap.tariff_profile_list_link.href);
            pt->put(path+".all", dcap.tariff_profile_list_link.all);
        }
        path = "DeviceCapability.TimeLink.<xmlattr>";
        if(dcap.time_link.href != ""){
            pt->put(path+".href", dcap.time_link.href);
        }
        path = "DeviceCapability.UsagePointListLink.<xmlattr>";
        if(dcap.usage_point_list_link.href != ""){
            pt->put(path+".href", dcap.usage_point_list_link.href);
            pt->put(path+".all", dcap.usage_point_list_link.all);
        }
        path = "DeviceCapability.EndDeviceListLink.<xmlattr>";
        if(dcap.end_device_list_link.href != ""){
            pt->put(path+".href", dcap.end_device_list_link.href);
            pt->put(path+".all", dcap.end_device_list_link.all);
        }
        path = "DeviceCapability.MirrorUsagePointListLink.<xmlattr>";
        if(dcap.mirror_usage_point_list_link.href != ""){
            pt->put(path+".href", dcap.mirror_usage_point_list_link.href);
            pt->put(path+".all", dcap.mirror_usage_point_list_link.all);
        }
        path = "DeviceCapability.SelfDeviceLink.<xmlattr>";
        if(dcap.self_device_link.href != ""){
            pt->put(path+".href", dcap.self_device_link.href);
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
