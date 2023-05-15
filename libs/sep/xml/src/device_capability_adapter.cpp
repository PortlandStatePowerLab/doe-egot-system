#include <sep/xml/device_capability_adapter.hpp>
#include <sep/xml/utilities.hpp>
#include <sep/models/simple_types.hpp>
#include <boost/optional.hpp>

namespace xml
{
    void ObjectMap(const boost::property_tree::ptree &pt, sep::DeviceCapability *dcap)
    {
        std::string path = "deviceCapability.<xmlattr>";
        if(pt.get<std::string>(path+".href", "") != ""){
            dcap->href = pt.get<std::string>(path+".href", "");
            dcap->poll_rate = pt.get<sep::UInt32>(path+".pollRate", 900);
        }
        path = "DeviceCapability.CustomerAccountListLink.<xmlattr>";
        if(pt.get<std::string>(path+".href", "") != ""){
            dcap->customer_account_list_link.href = pt.get<std::string>(path+".href", "");
            dcap->customer_account_list_link.all = pt.get<sep::UInt32>(path+".all", 0);
        }
        path = "DeviceCapability.DemandResponseProgramListLink.<xmlattr>";
        if(pt.get<std::string>(path+".href", "") != ""){
            dcap->demand_response_program_list_link.href = pt.get<std::string>(path+".href", "");
            dcap->demand_response_program_list_link.all = pt.get<sep::UInt32>(path+".all", 0);
        }
        path = "DeviceCapability.DERProgramListLink.<xmlattr>";
        if(pt.get<std::string>(path+".href", "") != ""){
            dcap->der_program_list_link.href = pt.get<std::string>(path+".href", "");
            dcap->der_program_list_link.all = pt.get<sep::UInt32>(path+".all", 0);
        }
        path = "DeviceCapability.FileListLink.<xmlattr>";
        if(pt.get<std::string>(path+".href", "") != ""){
            dcap->file_list_link.href = pt.get<std::string>(path+".href", "");
        }
        path = "DeviceCapability.MessagingProgramListLink.<xmlattr>";
        if(pt.get<std::string>(path+".href", "") != ""){
            dcap->messaging_program_list_link.href = pt.get<std::string>(path+".href", "");
            dcap->messaging_program_list_link.all = pt.get<sep::UInt32>(path+".all", 0);
        }
        path = "DeviceCapability.PrepaymentListLink.<xmlattr>";
        if(pt.get<std::string>(path+".href", "") != ""){
            dcap->prepayment_list_link.href = pt.get<std::string>(path+".href", "");
            dcap->prepayment_list_link.all = pt.get<sep::UInt32>(path+".all", 0);
        }
        path = "DeviceCapability.ResponseSetListLink.<xmlattr>";
        if(pt.get<std::string>(path+".href", "") != ""){
            dcap->response_set_list_link.href = pt.get<std::string>(path+".href", "");
            dcap->response_set_list_link.all = pt.get<sep::UInt32>(path+".all", 0);
        }
        path = "DeviceCapability.TariffProfileListLink.<xmlattr>";
        if(pt.get<std::string>(path+".href", "") != ""){
            dcap->tariff_profile_list_link.href = pt.get<std::string>(path+".href", "");
            dcap->tariff_profile_list_link.all = pt.get<sep::UInt32>(path+".all", 0);
        }
        path = "DeviceCapability.TimeLink.<xmlattr>";
        if(pt.get<std::string>(path+".href", "") != ""){
            dcap->time_link.href = pt.get<std::string>(path+".href", "");
        }
        path = "DeviceCapability.UsagePointListLink.<xmlattr>";
        if(pt.get<std::string>(path+".href", "") != ""){
            dcap->usage_point_list_link.href = pt.get<std::string>(path+".href", "");
            dcap->usage_point_list_link.all = pt.get<sep::UInt32>(path+".all", 0);
        }
        path = "DeviceCapability.EndDeviceListLink.<xmlattr>";
        if(pt.get<std::string>(path+".href", "") != ""){
            dcap->end_device_list_link.href = pt.get<std::string>(path+".href", "");
            dcap->end_device_list_link.all = pt.get<sep::UInt32>(path+".all", 0);
        }
        path = "DeviceCapability.MirrorUsagePointListLink.<xmlattr>";
        if(pt.get<std::string>(path+".href", "") != ""){
            dcap->mirror_usage_point_list_link.href = pt.get<std::string>(path+".href", "");
            dcap->mirror_usage_point_list_link.all = pt.get<sep::UInt32>(path+".all", 0);
        }
        path = "DeviceCapability.SelfDeviceLink.<xmlattr>";
        if(pt.get<std::string>(path+".href", "") != ""){
            dcap->self_device_link.href = pt.get<std::string>(path+".href", "");
        }
    };

    void TreeMap(const sep::DeviceCapability &dcap, boost::property_tree::ptree *pt)
    {
        std::string path = "DeviceCapability.<xmlattr>";
        if(dcap.href != ""){
            pt->put(path+".href", dcap.href);
            pt->put(path+".pollRate", dcap.poll_rate);
        }
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
