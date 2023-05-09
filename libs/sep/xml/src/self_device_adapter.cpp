#include <sep/xml/self_device_adapter.hpp>
#include <sep/xml/utilities.hpp>
#include <boost/foreach.hpp>

namespace xml
{
    void ObjectMap(const boost::property_tree::ptree &pt, sep::SelfDevice *sdev)
    {
        sdev->poll_rate = pt.get<sep::UInt32>("SelfDevice.<xmlattr>.pollRate", 900);
        sdev->subscribable = static_cast<sep::SubscribableType>(
            pt.get<uint8_t>("SelfDevice.<xmlattr>.subscribable", 0));
        sdev->href = pt.get<std::string>("SelfDevice.<xmlattr>.href", "");
        sdev->configuration_link.href = pt.get<std::string>("SelfDevice.ConfigurationLink.<xmlattr>.href", "");
        sdev->der_list_link.href = pt.get<std::string>("SelfDevice.DERListLink.<xmlattr>.href", "");
        sdev->der_list_link.all = pt.get<sep::UInt32>("SelfDevice.DERListLink.<xmlattr>.all", 0);
        sdev->device_category = static_cast<sep::DeviceCategoryType>(
            xml::util::Dehexify<sep::HexBinary32>(pt.get<std::string>("SelfDevice.deviceCategory", "00")));
        sdev->device_information_link.href = pt.get<std::string>("SelfDevice.DeviceInformationLink.<xmlattr>.href", "");
        sdev->device_status_link.href = pt.get<std::string>("SelfDevice.DeviceStatusLink.<xmlattr>.href", "");
        sdev->file_status_link.href = pt.get<std::string>("SelfDevice.FileStatusLink.<xmlattr>.href", "");
        sdev->ip_interface_list_link.href = pt.get<std::string>("SelfDevice.IPInterfaceListLink.<xmlattr>.href", "");
        sdev->ip_interface_list_link.all = pt.get<sep::UInt32>("SelfDevice.IPInterfaceListLink.<xmlattr>.all", 0);
        sdev->lfdi = xml::util::Dehexify<sep::HexBinary160>(pt.get<std::string>("SelfDevice.lFDI", ""));
        sdev->load_shed_availability_list_link.href = pt.get<std::string>("SelfDevice.LoadShedAvailabilityListLink.<xmlattr>.href", "");
        sdev->load_shed_availability_list_link.all = pt.get<sep::UInt32>("SelfDevice.LoadShedAvailabilityListLink.<xmlattr>.all", 0);
        sdev->log_event_list_link.href = pt.get<std::string>("SelfDevice.LogEventListLink.<xmlattr>.href", "");
        sdev->log_event_list_link.all = pt.get<sep::UInt32>("SelfDevice.LogEventListLink.<xmlattr>.all", 0);
        sdev->power_status_link.href = pt.get<std::string>("SelfDevice.PowerStatusLink.<xmlattr>.href", "");
        sdev->sfdi = pt.get<sep::SFDIType>("SelfDevice.sFDI", 0);
    };

    void TreeMap(const sep::SelfDevice &sdev, boost::property_tree::ptree *pt)
    {
        pt->put("SelfDevice.<xmlattr>.pollRate", sdev.poll_rate);
        pt->put("SelfDevice.<xmlattr>.subscribable", xml::util::ToUnderlyingType(sdev.subscribable));
        pt->put("SelfDevice.<xmlattr>.href", sdev.href);
        pt->put("SelfDevice.ConfigurationLink.<xmlattr>.href", sdev.configuration_link.href);
        pt->put("SelfDevice.DERListLink.<xmlattr>.href", sdev.der_list_link.href);
        pt->put("SelfDevice.DERListLink.<xmlattr>.all", sdev.der_list_link.all);
        pt->put("SelfDevice.deviceCategory", xml::util::Hexify(xml::util::ToUnderlyingType(sdev.device_category)));
        pt->put("SelfDevice.DeviceInformationLink.<xmlattr>.href", sdev.device_information_link.href);
        pt->put("SelfDevice.DeviceStatusLink.<xmlattr>.href", sdev.device_status_link.href);
        pt->put("SelfDevice.FileStatusLink.<xmlattr>.href", sdev.file_status_link.href);
        pt->put("SelfDevice.IPInterfaceListLink.<xmlattr>.href", sdev.ip_interface_list_link.href);
        pt->put("SelfDevice.IPInterfaceListLink.<xmlattr>.all", sdev.ip_interface_list_link.all);
        pt->put("SelfDevice.lFDI", xml::util::Hexify(sdev.lfdi));
        pt->put("SelfDevice.LoadShedAvailabilityListLink.<xmlattr>.href", sdev.load_shed_availability_list_link.href);
        pt->put("SelfDevice.LoadShedAvailabilityListLink.<xmlattr>.all", sdev.load_shed_availability_list_link.all);
        pt->put("SelfDevice.LogEventListLink.<xmlattr>.href", sdev.log_event_list_link.href);
        pt->put("SelfDevice.LogEventListLink.<xmlattr>.all", sdev.log_event_list_link.all);
        pt->put("SelfDevice.PowerStatusLink.<xmlattr>.href", sdev.power_status_link.href);
        pt->put("SelfDevice.sFDI", sdev.sfdi);
    };

    std::string Serialize(const sep::SelfDevice &sdev)
    {
        boost::property_tree::ptree pt;
        TreeMap(sdev, &pt);

        xml::util::SetSchema(&pt);
        return xml::util::Stringify(&pt);
    };

    void Parse(const std::string &xml_str, sep::SelfDevice *sdev)
    {
        boost::property_tree::ptree pt = xml::util::Treeify(xml_str);
        ObjectMap(pt, sdev);
    };

} // namespace xml
