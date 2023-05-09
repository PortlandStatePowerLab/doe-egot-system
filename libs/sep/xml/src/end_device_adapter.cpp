#include <sep/xml/end_device_adapter.hpp>
#include <sep/xml/utilities.hpp>
#include <boost/foreach.hpp>

namespace xml
{

    void ObjectMap(const boost::property_tree::ptree &pt, sep::EndDevice *edev)
    {
        edev->subscribable = static_cast<sep::SubscribableType>(
            pt.get<sep::UInt8>("EndDevice.<xmlattr>.subscribable", 0));
        edev->href = pt.get<std::string>("EndDevice.<xmlattr>.href", "");
        edev->configuration_link.href = pt.get<std::string>("EndDevice.ConfigurationLink.<xmlattr>.href", "");
        edev->der_list_link.href = pt.get<std::string>("EndDevice.DERListLink.<xmlattr>.href", "");
        edev->der_list_link.all = pt.get<sep::UInt32>("EndDevice.DERListLink.<xmlattr>.all", 0);
        edev->device_category = static_cast<sep::DeviceCategoryType>(
            xml::util::Dehexify<sep::HexBinary32>(pt.get<std::string>("EndDevice.deviceCategory", "00")));
        edev->device_information_link.href = pt.get<std::string>("EndDevice.DeviceInformationLink.<xmlattr>.href", "");
        edev->device_status_link.href = pt.get<std::string>("EndDevice.DeviceStatusLink.<xmlattr>.href", "");
        edev->file_status_link.href = pt.get<std::string>("EndDevice.FileStatusLink.<xmlattr>.href", "");
        edev->ip_interface_list_link.href = pt.get<std::string>("EndDevice.IPInterfaceListLink.<xmlattr>.href", "");
        edev->ip_interface_list_link.all = pt.get<sep::UInt32>("EndDevice.IPInterfaceListLink.<xmlattr>.all", 0);
        edev->lfdi = xml::util::Dehexify<sep::HexBinary160>(pt.get<std::string>("EndDevice.lFDI", ""));
        edev->load_shed_availability_list_link.href = pt.get<std::string>("EndDevice.LoadShedAvailabilityListLink.<xmlattr>.href", "");
        edev->load_shed_availability_list_link.all = pt.get<sep::UInt32>("EndDevice.LoadShedAvailabilityListLink.<xmlattr>.all", 0);
        edev->log_event_list_link.href = pt.get<std::string>("EndDevice.LogEventListLink.<xmlattr>.href", "");
        edev->log_event_list_link.all = pt.get<sep::UInt32>("EndDevice.LogEventListLink.<xmlattr>.all", 0);
        edev->power_status_link.href = pt.get<std::string>("EndDevice.PowerStatusLink.<xmlattr>.href", "");
        edev->sfdi = pt.get<sep::SFDIType>("EndDevice.sFDI", 0);
        edev->changed_time = pt.get<sep::TimeType>("EndDevice.changedTime", 0);
        edev->enabled = pt.get<bool>("EndDevice.enabled", false);
        edev->flow_reservation_request_list_link.href = pt.get<std::string>("EndDevice.FlowReservationRequestListLink.<xmlattr>.href", "");
        edev->flow_reservation_request_list_link.all = pt.get<sep::UInt32>("EndDevice.FlowReservationRequestListLink.<xmlattr>.all", 0);
        edev->flow_reservation_response_list_link.href = pt.get<std::string>("EndDevice.FlowReservationResponseListLink.<xmlattr>.href", "");
        edev->flow_reservation_response_list_link.all = pt.get<sep::UInt32>("EndDevice.FlowReservationResponseListLink.<xmlattr>.all", 0);
        edev->function_set_assignments_list_link.href = pt.get<std::string>("EndDevice.FunctionSetAssignmentsListLink.<xmlattr>.href", "");
        edev->function_set_assignments_list_link.all = pt.get<sep::UInt32>("EndDevice.FunctionSetAssignmentsListLink.<xmlattr>.all", 0);
        edev->post_rate = pt.get<sep::UInt32>("EndDevice.postRate", 0);
        edev->registration_link.href = pt.get<std::string>("EndDevice.RegistrationLink.<xmlattr>.href", "");
        edev->subscription_list_link.href = pt.get<std::string>("EndDevice.SubscriptionListLink.<xmlattr>.href", "");
        edev->subscription_list_link.all = pt.get<sep::UInt32>("EndDevice.SubscriptionListLink.<xmlattr>.all", 0);
    };

    void TreeMap(const sep::EndDevice &edev, boost::property_tree::ptree *pt)
    {
        pt->put("EndDevice.<xmlattr>.subscribable", xml::util::ToUnderlyingType(edev.subscribable));
        pt->put("EndDevice.<xmlattr>.href", edev.href);
        pt->put("EndDevice.ConfigurationLink.<xmlattr>.href", edev.configuration_link.href);
        pt->put("EndDevice.DERListLink.<xmlattr>.href", edev.der_list_link.href);
        pt->put("EndDevice.DERListLink.<xmlattr>.all", edev.der_list_link.all);
        pt->put("EndDevice.deviceCategory", xml::util::Hexify(xml::util::ToUnderlyingType(edev.device_category)));
        pt->put("EndDevice.DeviceInformationLink.<xmlattr>.href", edev.device_information_link.href);
        pt->put("EndDevice.DeviceStatusLink.<xmlattr>.href", edev.device_status_link.href);
        pt->put("EndDevice.FileStatusLink.<xmlattr>.href", edev.file_status_link.href);
        pt->put("EndDevice.IPInterfaceListLink.<xmlattr>.href", edev.ip_interface_list_link.href);
        pt->put("EndDevice.IPInterfaceListLink.<xmlattr>.all", edev.ip_interface_list_link.all);
        pt->put("EndDevice.lFDI", xml::util::Hexify(edev.lfdi));
        pt->put("EndDevice.LoadShedAvailabilityListLink.<xmlattr>.href", edev.load_shed_availability_list_link.href);
        pt->put("EndDevice.LoadShedAvailabilityListLink.<xmlattr>.all", edev.load_shed_availability_list_link.all);
        pt->put("EndDevice.LogEventListLink.<xmlattr>.href", edev.log_event_list_link.href);
        pt->put("EndDevice.LogEventListLink.<xmlattr>.all", edev.log_event_list_link.all);
        pt->put("EndDevice.PowerStatusLink.<xmlattr>.href", edev.power_status_link.href);
        pt->put("EndDevice.sFDI", edev.sfdi);
        pt->put("EndDevice.changedTime", edev.changed_time);
        pt->put("EndDevice.enabled", edev.enabled);
        pt->put("EndDevice.FlowReservationRequestListLink.<xmlattr>.href", edev.flow_reservation_request_list_link.href);
        pt->put("EndDevice.FlowReservationRequestListLink.<xmlattr>.all", edev.flow_reservation_request_list_link.all);
        pt->put("EndDevice.FlowReservationResponseListLink.<xmlattr>.href", edev.flow_reservation_response_list_link.href);
        pt->put("EndDevice.FlowReservationResponseListLink.<xmlattr>.all", edev.flow_reservation_response_list_link.all);
        pt->put("EndDevice.FunctionSetAssignmentsListLink.<xmlattr>.href", edev.function_set_assignments_list_link.href);
        pt->put("EndDevice.FunctionSetAssignmentsListLink.<xmlattr>.all", edev.function_set_assignments_list_link.all);
        pt->put("EndDevice.postRate", edev.post_rate);
        pt->put("EndDevice.RegistrationLink.<xmlattr>.href", edev.registration_link.href);
        pt->put("EndDevice.SubscriptionListLink.<xmlattr>.href", edev.subscription_list_link.href);
        pt->put("EndDevice.SubscriptionListLink.<xmlattr>.all", edev.subscription_list_link.all);
    };

    std::string Serialize(const sep::EndDevice &edev)
    {
        boost::property_tree::ptree pt;
        TreeMap(edev, &pt);

        xml::util::SetSchema(&pt);
        return xml::util::Stringify(&pt);
    };

    void Parse(const std::string &xml_str, sep::EndDevice *edev)
    {
        boost::property_tree::ptree pt = xml::util::Treeify(xml_str);
        ObjectMap(pt, edev);
    };

    std::string Serialize(const sep::EndDeviceList &edev_list)
    {
        boost::property_tree::ptree pt;
        pt.put("EndDeviceList.<xmlattr>.all", edev_list.all);
        pt.put("EndDeviceList.<xmlattr>.results", edev_list.end_devices.size());
        pt.put("EndDeviceList.<xmlattr>.href", edev_list.href);
        pt.put("EndDeviceList.<xmlattr>.pollRate", edev_list.poll_rate);

        for (const auto& edev : edev_list.end_devices)
        {
            boost::property_tree::ptree pt2;
            TreeMap(edev, &pt2);
            pt.add_child("EndDeviceList.EndDevice", pt2.get_child("EndDevice"));
        }
        
        xml::util::SetSchema(&pt);
        return xml::util::Stringify(&pt);
    };

    void Parse(const std::string &xml_str, sep::EndDeviceList *edevs)
    {
        boost::property_tree::ptree pt = xml::util::Treeify(xml_str);
        edevs->all = pt.get<sep::UInt32>("EndDeviceList.<xmlattr>.all", 0);
        edevs->href = pt.get<std::string>("EndDeviceList.<xmlattr>.href", "");
        edevs->results = pt.get<sep::UInt32>("EndDeviceList.<xmlattr>.results", 0);
        edevs->poll_rate = pt.get<sep::UInt32>("EndDeviceList.<xmlattr>.pollRate", 900);

        BOOST_FOREACH (boost::property_tree::ptree::value_type &subtree, pt.get_child("EndDeviceList"))
        {
            if (subtree.first == "EndDevice")
            {
                boost::property_tree::ptree temp;
                temp.add_child("EndDevice", subtree.second);

                sep::EndDevice edev;
                ObjectMap(temp, &edev);
                edevs->end_devices.emplace_back(edev);
            }
        }
    };
} // namespace xml
