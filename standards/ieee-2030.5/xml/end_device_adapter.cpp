#include "include/xml/end_device_adapter.hpp"
#include <boost/foreach.hpp>
#include "include/xml/utilities.hpp"

namespace xml
{

    void ObjectMap(const boost::property_tree::ptree &pt, sep::EndDevice *edev)
    {
        edev->subscribable = static_cast<sep::SubscribableType>(
            pt.get<uint8_t>("EndDevice.<xmlattr>.subscribable", 0));
        edev->href = pt.get<std::string>("EndDevice.<xmlattr>.href", "");
        edev->configuration_link.href = pt.get<std::string>("EndDevice.ConfigurationLink.<xmlattr>.href", "");
        edev->der_list_link.href = pt.get<std::string>("EndDevice.DERListLink.<xmlattr>.href", "");
        edev->der_list_link.all = pt.get<uint32_t>("EndDevice.DERListLink.<xmlattr>.all", 0);
        edev->device_category = static_cast<sep::DeviceCategoryType>(
            xml::util::Dehexify<uint32_t>(pt.get<std::string>("EndDevice.deviceCategory", "00")));
        edev->device_information_link.href = pt.get<std::string>("EndDevice.DeviceInformationLink.<xmlattr>.href", "");
        edev->device_status_link.href = pt.get<std::string>("EndDevice.DeviceStatusLink.<xmlattr>.href", "");
        edev->file_status_link.href = pt.get<std::string>("EndDevice.FileStatusLink.<xmlattr>.href", "");
        edev->ip_interface_list_link.href = pt.get<std::string>("EndDevice.IPInterfaceListLink.<xmlattr>.href", "");
        edev->ip_interface_list_link.all = pt.get<uint32_t>("EndDevice.IPInterfaceListLink.<xmlattr>.all", 0);
        edev->lfdi = xml::util::Dehexify<boost::multiprecision::uint256_t>(pt.get<std::string>("EndDevice.lFDI", ""));
        edev->load_shed_availability_list_link.href = pt.get<std::string>("EndDevice.LoadShedAvailabilityListLink.<xmlattr>.href", "");
        edev->load_shed_availability_list_link.all = pt.get<uint32_t>("EndDevice.LoadShedAvailabilityListLink.<xmlattr>.all", 0);
        edev->log_event_list_link.href = pt.get<std::string>("EndDevice.LogEventListLink.<xmlattr>.href", "");
        edev->log_event_list_link.all = pt.get<uint32_t>("EndDevice.LogEventListLink.<xmlattr>.all", 0);
        edev->power_status_link.href = pt.get<std::string>("EndDevice.PowerStatusLink.<xmlattr>.href", "");
        edev->sfdi = pt.get<uint64_t>("EndDevice.sFDI", 0);
        edev->changed_time = pt.get<sep::TimeType>("EndDevice.changedTime", 0);
        edev->enabled = pt.get<bool>("EndDevice.enabled", false);
        edev->flow_reservation_request_list_link.href = pt.get<std::string>("EndDevice.FlowReservationRequestListLink.<xmlattr>.href", "");
        edev->flow_reservation_request_list_link.all = pt.get<uint32_t>("EndDevice.FlowReservationRequestListLink.<xmlattr>.all", 0);
        edev->flow_reservation_response_list_link.href = pt.get<std::string>("EndDevice.FlowReservationResponseListLink.<xmlattr>.href", "");
        edev->flow_reservation_response_list_link.all = pt.get<uint32_t>("EndDevice.FlowReservationResponseListLink.<xmlattr>.all", 0);
        edev->function_set_assignments_list_link.href = pt.get<std::string>("EndDevice.FunctionSetAssignmentsListLink.<xmlattr>.href", "");
        edev->function_set_assignments_list_link.all = pt.get<uint32_t>("EndDevice.FunctionSetAssignmentsListLink.<xmlattr>.all", 0);
        edev->post_rate = pt.get<uint32_t>("EndDevice.postRate", 0);
        edev->registration_link.href = pt.get<std::string>("EndDevice.RegistrationLink.<xmlattr>.href", "");
        edev->subscription_list_link.href = pt.get<std::string>("EndDevice.SubscriptionListLink.<xmlattr>.href", "");
        edev->subscription_list_link.all = pt.get<uint32_t>("EndDevice.SubscriptionListLink.<xmlattr>.all", 0);
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

    std::string Serialize(const std::vector<sep::EndDevice> &edev_list, const sep::List& list)
    {
        boost::property_tree::ptree pt;
        pt.put("EndDeviceList.<xmlattr>.all", list.all);
        pt.put("EndDeviceList.<xmlattr>.results", list.results);
        pt.put("EndDeviceList.<xmlattr>.href", list.href);

        for (const auto& edev : edev_list)
        {
            boost::property_tree::ptree pt2;
            TreeMap(edev, &pt2);
            pt.add_child("EndDeviceList.EndDevice", pt2.get_child("EndDevice"));
        }
        
        xml::util::SetSchema(&pt);
        return xml::util::Stringify(&pt);
    };

    void Parse(const std::string &xml_str, std::vector<sep::EndDevice> *edevs)
    {
        boost::property_tree::ptree pt = xml::util::Treeify(xml_str);
        BOOST_FOREACH (boost::property_tree::ptree::value_type &subtree, pt.get_child("EndDeviceList"))
        {
            if (subtree.first == "EndDevice")
            {
                boost::property_tree::ptree temp;
                temp.add_child("EndDevice", subtree.second);

                sep::EndDevice edev;
                ObjectMap(temp, &edev);
                edevs->emplace_back(edev);
            }
        }
    };
} // namespace xml
