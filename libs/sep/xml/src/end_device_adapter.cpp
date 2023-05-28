#include <boost/foreach.hpp>
#include <sep/xml/end_device_adapter.hpp>
#include <sep/xml/utilities.hpp>

namespace xml {

void ObjectMap(const boost::property_tree::ptree &pt, sep::EndDevice *edev) {
  std::string path = "EndDevice.changedTime";
  edev->changed_time = pt.get<sep::TimeType>(path, 0);
  path = "EndDevice.<xmlattr>.href";
  edev->href = pt.get<std::string>(path, "");
  path = "EndDevice.sFDI";
  edev->sfdi = pt.get<sep::SFDIType>(path, 0);
  path = "EndDevice.<xmlattr>.subscribable";
  edev->subscribable =
      static_cast<sep::SubscribableType>(pt.get<sep::UInt8>(path, 0));
  path = "EndDevice.ConfigurationLink.<xmlattr>.href";
  if (auto href = pt.get_optional<std::string>(path)) {
    sep::ConfigurationLink link = {};
    link.href = href.value();
    edev->configuration_link.emplace(link);
  }
  path = "DeviceCapability.DERListLink";
  if (auto child = pt.get_child_optional(path)) {
    auto href = child.value().get<std::string>("<xmlattr>.href", "");
    auto all = child.value().get<sep::UInt32>("<xmlattr>.all", 900);
    sep::DERListLink link_list = {};
    link_list.href = href;
    link_list.all = all;
    edev->der_list_link.emplace(link_list);
  }
  path = "EndDevice.deviceCategory";
  if (auto device_category = pt.get_optional<sep::HexBinary32>(path)) {
    sep::DeviceCategoryType category =
        static_cast<sep::DeviceCategoryType>(device_category.value());
    edev->device_category.emplace(category);
  }
  path = "EndDevice.DeviceInformationLink.<xmlattr>.href";
  if (auto href = pt.get_optional<std::string>(path)) {
    sep::DeviceInformationLink link = {};
    link.href = href.value();
    edev->device_information_link.emplace(link);
  }
  path = "EndDevice.DeviceStatusLink.<xmlattr>.href";
  if (auto href = pt.get_optional<std::string>(path)) {
    sep::DeviceStatusLink link = {};
    link.href = href.value();
    edev->device_status_link.emplace(link);
  }
  path = "EndDevice.FileStatusLink.<xmlattr>.href";
  if (auto href = pt.get_optional<std::string>(path)) {
    sep::FileStatusLink link = {};
    link.href = href.value();
    edev->file_status_link.emplace(link);
  }
  path = "EndDevice.IPInterfaceListLink";
  if (auto child = pt.get_child_optional(path)) {
    auto href = child.value().get<std::string>("<xmlattr>.href", "");
    auto all = child.value().get<sep::UInt32>("<xmlattr>.all", 900);
    sep::IPInterfaceListLink link_list = {};
    link_list.href = href;
    link_list.all = all;
    edev->ip_interface_list_link.emplace(link_list);
  }
  path = "EndDevice.lFDI";
  if (auto lfdi = pt.get_optional<sep::HexBinary160>(path)) {
    edev->lfdi.emplace(lfdi.value());
  }
  path = "EndDevice.LoadShedAvailabilityListLink";
  if (auto child = pt.get_child_optional(path)) {
    auto href = child.value().get<std::string>("<xmlattr>.href", "");
    auto all = child.value().get<sep::UInt32>("<xmlattr>.all", 900);
    sep::LoadShedAvailabilityListLink link_list = {};
    link_list.href = href;
    link_list.all = all;
    edev->load_shed_availability_list_link.emplace(link_list);
  }
  path = "EndDevice.LogEventListLink";
  if (auto child = pt.get_child_optional(path)) {
    auto href = child.value().get<std::string>("<xmlattr>.href", "");
    auto all = child.value().get<sep::UInt32>("<xmlattr>.all", 900);
    sep::LogEventListLink link_list = {};
    link_list.href = href;
    link_list.all = all;
    edev->log_event_list_link.emplace(link_list);
  }
  path = "EndDevice.PowerStatusLink.<xmlattr>.href";
  if (auto href = pt.get_optional<std::string>(path)) {
    sep::PowerStatusLink link = {};
    link.href = href.value();
    edev->power_status_link.emplace(link);
  }
  path = "EndDevice.enabled";
  if (auto enabled = pt.get_optional<bool>(path)) {
    edev->enabled.emplace(enabled.value());
  }
  path = "EndDevice.FlowReservationRequestListLink";
  if (auto child = pt.get_child_optional(path)) {
    auto href = child.value().get<std::string>("<xmlattr>.href", "");
    auto all = child.value().get<sep::UInt32>("<xmlattr>.all", 900);
    sep::FlowReservationRequestListLink link_list = {};
    link_list.href = href;
    link_list.all = all;
    edev->flow_reservation_request_list_link.emplace(link_list);
  }
  path = "EndDevice.FlowReservationResponseListLink";
  if (auto child = pt.get_child_optional(path)) {
    auto href = child.value().get<std::string>("<xmlattr>.href", "");
    auto all = child.value().get<sep::UInt32>("<xmlattr>.all", 900);
    sep::FlowReservationResponseListLink link_list = {};
    link_list.href = href;
    link_list.all = all;
    edev->flow_reservation_response_list_link.emplace(link_list);
  }
  path = "EndDevice.FunctionSetAssignmentsListLink";
  if (auto child = pt.get_child_optional(path)) {
    auto href = child.value().get<std::string>("<xmlattr>.href", "");
    auto all = child.value().get<sep::UInt32>("<xmlattr>.all", 900);
    sep::FunctionSetAssignmentsListLink link_list = {};
    link_list.href = href;
    link_list.all = all;
    edev->function_set_assignments_list_link.emplace(link_list);
  }
  path = "EndDevice.postRate";
  if (auto rate = pt.get_optional<sep::UInt32>(path)) {
    edev->post_rate.emplace(rate.value());
  }
  path = "EndDevice.RegistrationLink.<xmlattr>.href";
  if (auto href = pt.get_optional<std::string>(path)) {
    sep::RegistrationLink link = {};
    link.href = href.value();
    edev->registration_link.emplace(link);
  }
  path = "EndDevice.SubscriptionListLink";
  if (auto child = pt.get_child_optional(path)) {
    auto href = child.value().get<std::string>("<xmlattr>.href", "");
    auto all = child.value().get<sep::UInt32>("<xmlattr>.all", 900);
    sep::SubscriptionListLink link_list = {};
    link_list.href = href;
    link_list.all = all;
    edev->subscription_list_link.emplace(link_list);
  }
};

void TreeMap(const sep::EndDevice &edev, boost::property_tree::ptree *pt) {
  std::string path = "EndDevice.<xmlattr>.href";
  pt->put(path, edev.href);
  path = "EndDevice.changedTime";
  pt->put(path, edev.changed_time);
  path = "EndDevice.sFDI";
  pt->put(path, edev.sfdi);
  path = "EndDevice.<xmlattr>.subscribable";
  pt->put(path, xml::util::ToUnderlyingType(edev.subscribable));
  if (edev.configuration_link.has_value()) {
    path = "EndDevice.ConfigurationLink.<xmlattr>.href";
    pt->put(path, edev.configuration_link.value().href);
  }
  if (edev.der_list_link.has_value()) {
    path = "EndDevice.DERListLink.<xmlattr>.href";
    pt->put(path, edev.der_list_link.value().href);
    path = "EndDevice.DERListLink.<xmlattr>.all";
    pt->put(path, edev.der_list_link.value().all);
  }
  if (edev.device_category.has_value()) {
    path = "EndDevice.deviceCategory";
    pt->put(path, xml::util::ToUnderlyingType(edev.device_category.value()));
  }
  if (edev.device_information_link.has_value()) {
    path = "EndDevice.DeviceInformationLink.<xmlattr>.href";
    pt->put(path, edev.device_information_link.value().href);
  }
  if (edev.device_status_link.has_value()) {
    path = "EndDevice.DeviceStatusLink.<xmlattr>.href";
    pt->put(path, edev.device_status_link.value().href);
  }
  if (edev.file_status_link.has_value()) {
    path = "EndDevice.FileStatusLink.<xmlattr>.href";
    pt->put(path, edev.file_status_link.value().href);
  }
  if (edev.ip_interface_list_link.has_value()) {
    path = "EndDevice.IPInterfaceListLink.<xmlattr>.href";
    pt->put(path, edev.ip_interface_list_link.value().href);
    path = "EndDevice.IPInterfaceListLink.<xmlattr>.all";
    pt->put(path, edev.ip_interface_list_link.value().all);
  }
  if (edev.lfdi.has_value()) {
    path = "EndDevice.lFDI";
    pt->put(path, xml::util::Hexify(edev.lfdi.value()));
  }
  if (edev.load_shed_availability_list_link.has_value()) {
    path = "EndDevice.LoadShedAvailabilityListLink.<xmlattr>.href";
    pt->put(path, edev.load_shed_availability_list_link.value().href);
    path = "EndDevice.LoadShedAvailabilityListLink.<xmlattr>.all";
    pt->put(path, edev.load_shed_availability_list_link.value().all);
  }
  if (edev.log_event_list_link.has_value()) {
    path = "EndDevice.LogEventListLink.<xmlattr>.href";
    pt->put(path, edev.log_event_list_link.value().href);
    path = "EndDevice.LogEventListLink.<xmlattr>.all";
    pt->put(path, edev.log_event_list_link.value().all);
  }
  if (edev.power_status_link.has_value()) {
    path = "EndDevice.PowerStatusLink.<xmlattr>.href";
    pt->put(path, edev.power_status_link.value().href);
  }
  if (edev.enabled.has_value()) {
    path = "EndDevice.enabled";
    pt->put(path, edev.enabled.value());
  }
  if (edev.flow_reservation_request_list_link.has_value()) {
    path = "EndDevice.FlowReservationRequestListLink.<xmlattr>.href";
    pt->put(path, edev.flow_reservation_request_list_link.value().href);
    path = "EndDevice.FlowReservationRequestListLink.<xmlattr>.all";
    pt->put(path, edev.flow_reservation_request_list_link.value().all);
  }
  if (edev.flow_reservation_response_list_link.has_value()) {
    path = "EndDevice.FlowReservationResponseListLink.<xmlattr>.href";
    pt->put(path, edev.flow_reservation_response_list_link.value().href);
    path = "EndDevice.FlowReservationResponseListLink.<xmlattr>.all";
    pt->put(path, edev.flow_reservation_response_list_link.value().all);
  }
  if (edev.function_set_assignments_list_link.has_value()) {
    path = "EndDevice.FunctionSetAssignmentsListLink.<xmlattr>.href";
    pt->put(path, edev.function_set_assignments_list_link.value().href);
    path = "EndDevice.FunctionSetAssignmentsListLink.<xmlattr>.all";
    pt->put(path, edev.function_set_assignments_list_link.value().all);
  }
  if (edev.post_rate.has_value()) {
    path = "EndDevice.postRate";
    pt->put(path, edev.post_rate.value());
  }
  if (edev.registration_link.has_value()) {
    pt->put("EndDevice.RegistrationLink.<xmlattr>.href",
            edev.registration_link.value().href);
  }
  if (edev.subscription_list_link.has_value()) {
    path = "EndDevice.SubscriptionListLink.<xmlattr>.href";
    pt->put(path, edev.subscription_list_link.value().href);
    path = "EndDevice.SubscriptionListLink.<xmlattr>.all";
    pt->put(path, edev.subscription_list_link.value().all);
  }
};

std::string Serialize(const sep::EndDevice &edev) {
  boost::property_tree::ptree pt;
  TreeMap(edev, &pt);

  xml::util::SetSchema(&pt);
  return xml::util::Stringify(&pt);
};

void Parse(const std::string &xml_str, sep::EndDevice *edev) {
  boost::property_tree::ptree pt = xml::util::Treeify(xml_str);
  ObjectMap(pt, edev);
};

std::string Serialize(const sep::EndDeviceList &edev_list) {
  boost::property_tree::ptree pt;
  pt.put("EndDeviceList.<xmlattr>.all", edev_list.all);
  pt.put("EndDeviceList.<xmlattr>.results", edev_list.end_devices.size());
  pt.put("EndDeviceList.<xmlattr>.href", edev_list.href);
  pt.put("EndDeviceList.<xmlattr>.pollRate", edev_list.poll_rate);

  for (const auto &edev : edev_list.end_devices) {
    boost::property_tree::ptree pt2;
    TreeMap(edev, &pt2);
    pt.add_child("EndDeviceList.EndDevice", pt2.get_child("EndDevice"));
  }

  xml::util::SetSchema(&pt);
  return xml::util::Stringify(&pt);
};

void Parse(const std::string &xml_str, sep::EndDeviceList *edevs) {
  boost::property_tree::ptree pt = xml::util::Treeify(xml_str);
  edevs->all = pt.get<sep::UInt32>("EndDeviceList.<xmlattr>.all", 0);
  edevs->href = pt.get<std::string>("EndDeviceList.<xmlattr>.href", "");
  edevs->results = pt.get<sep::UInt32>("EndDeviceList.<xmlattr>.results", 0);
  edevs->poll_rate =
      pt.get<sep::UInt32>("EndDeviceList.<xmlattr>.pollRate", 900);

  BOOST_FOREACH (boost::property_tree::ptree::value_type &subtree,
                 pt.get_child("EndDeviceList")) {
    if (subtree.first == "EndDevice") {
      boost::property_tree::ptree temp;
      temp.add_child("EndDevice", subtree.second);

      sep::EndDevice edev;
      ObjectMap(temp, &edev);
      edevs->end_devices.emplace_back(edev);
    }
  }
};
} // namespace xml
