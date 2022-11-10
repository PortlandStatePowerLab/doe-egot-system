#include "include/xml/self_device_adapter.hpp"
#include <boost/foreach.hpp>
#include "include/xml/utilities.hpp"

namespace xml
{
    void ObjectMap(const boost::property_tree::ptree &pt, sep::SelfDevice *sdev)
    {
        sdev->poll_rate = pt.get<uint32_t>("SelfDevice.<xmlattr>.pollRate", 900);
        sdev->subscribable = static_cast<sep::SubscribableType>(
            pt.get<uint8_t>("SelfDevice.<xmlattr>.subscribable", 0));
        sdev->href = pt.get<std::string>("SelfDevice.<xmlattr>.href", "");
        sdev->configuration_link.href = pt.get<std::string>("SelfDevice.ConfigurationLink.<xmlattr>.href", "");
        sdev->der_list_link.href = pt.get<std::string>("SelfDevice.DERListLink.<xmlattr>.href", "");
        sdev->der_list_link.all = pt.get<uint32_t>("SelfDevice.DERListLink.<xmlattr>.all", 0);
        sdev->device_category = static_cast<sep::DeviceCategoryType>(
            xml::util::Dehexify<uint32_t>(pt.get<std::string>("SelfDevice.deviceCategory", "00")));
        sdev->device_information_link.href = pt.get<std::string>("SelfDevice.DeviceInformationLink.<xmlattr>.href", "");
        sdev->device_status_link.href = pt.get<std::string>("SelfDevice.DeviceStatusLink.<xmlattr>.href", "");
        sdev->file_status_link.href = pt.get<std::string>("SelfDevice.FileStatusLink.<xmlattr>.href", "");
        sdev->ip_interface_list_link.href = pt.get<std::string>("SelfDevice.IPInterfaceListLink.<xmlattr>.href", "");
        sdev->ip_interface_list_link.all = pt.get<uint32_t>("SelfDevice.IPInterfaceListLink.<xmlattr>.all", 0);
        sdev->lfdi = xml::util::Dehexify<sep::LFDIType>(pt.get<std::string>("SelfDevice.lFDI", ""));
        sdev->load_shed_availability_list_link.href = pt.get<std::string>("SelfDevice.LoadShedAvailabilityListLink.<xmlattr>.href", "");
        sdev->load_shed_availability_list_link.all = pt.get<uint32_t>("SelfDevice.LoadShedAvailabilityListLink.<xmlattr>.all", 0);
        sdev->log_event_list_link.href = pt.get<std::string>("SelfDevice.LogEventListLink.<xmlattr>.href", "");
        sdev->log_event_list_link.all = pt.get<uint32_t>("SelfDevice.LogEventListLink.<xmlattr>.all", 0);
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

    std::string Serialize(const std::vector<sep::SelfDevice> &sdev_list, const sep::List& list)
    {
        boost::property_tree::ptree pt;
        pt.put("SelfDeviceList.<xmlattr>.all", list.all);
        pt.put("SelfDeviceList.<xmlattr>.results", list.results);
        pt.put("SelfDeviceList.<xmlattr>.href", list.href);
        pt.put("SelfDeviceList.<xmlattr>.pollRate", list.inherited_poll_rate);

        for (const auto& sdev : sdev_list)
        {
            boost::property_tree::ptree pt2;
            TreeMap(sdev, &pt2);
            pt.add_child("SelfDeviceList.SelfDevice", pt2.get_child("SelfDevice"));
        }
        
        xml::util::SetSchema(&pt);
        return xml::util::Stringify(&pt);
    };

    void Parse(const std::string &xml_str, std::vector<sep::SelfDevice> *sdevs)
    {
        boost::property_tree::ptree pt = xml::util::Treeify(xml_str);
        BOOST_FOREACH (boost::property_tree::ptree::value_type &subtree, pt.get_child("SelfDeviceList"))
        {
            if (subtree.first == "SelfDevice")
            {
                boost::property_tree::ptree temp;
                temp.add_child("SelfDevice", subtree.second);

                sep::SelfDevice sdev;
                ObjectMap(temp, &sdev);
                sdev.inherited_poll_rate = pt.get<uint32_t>("SelfDeviceList.<xmlattr>.pollRate", 900);
                sdevs->emplace_back(sdev);
            }
        }
    };
} // namespace xml
