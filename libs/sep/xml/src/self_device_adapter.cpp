#include <boost/foreach.hpp>
#include <sep/xml/self_device_adapter.hpp>
#include <sep/xml/utilities.hpp>

namespace xml {
void ObjectMap(const boost::property_tree::ptree &pt, sep::SelfDevice *sdev) {
  std::string path = "SelfDevice.<xmlattr>.href";
  sdev->href = pt.get<std::string>(path, "");
  path = "SelfDevice.<xmlattr>.pollRate";
  sdev->poll_rate = pt.get<sep::UInt32>(path, 900);
  path = "SelfDevice.<xmlattr>.subscribable";
  sdev->subscribable = static_cast<sep::SubscribableType>(pt.get<sep::UInt8>(path, 0));
  path = "SelfDevice.sFDI";
  sdev->sfdi = pt.get<sep::SFDIType>(path, 0);
  path = "DeviceCapability.ConfigurationLink.<xmlattr>.href";
  if (auto href = pt.get_optional<std::string>(path)) {
    sep::ConfigurationLink link = {};
    link.href = href.value();
    sdev->configuration_link.emplace(link);
  }
  path = "SelfDevice.DERListLink";
  if (auto child = pt.get_child_optional(path)) {
    auto href = child.value().get<std::string>("<xmlattr>.href", "");
    auto all = child.value().get<sep::UInt32>("<xmlattr>.all", 900);
    sep::DERListLink link_list = {};
    link_list.href = href;
    link_list.all = all;
    sdev->der_list_link.emplace(link_list);
  }
  path = "SelfDevice.deviceCategory";
  if (auto category = pt.get_optional<std::string>(path)) {
    auto hex = xml::util::Dehexify<sep::HexBinary32>(category.value());
    sdev->device_category.emplace(static_cast<sep::DeviceCategoryType>(hex));
  }
  path = "SelfDevice.DeviceInformationLink.<xmlattr>.href";
  if (auto href = pt.get_optional<std::string>(path)) {
    sep::DeviceInformationLink link = {};
    link.href = href.value();
    sdev->device_information_link.emplace(link);
  }
  path = "SelfDevice.DeviceStatusLink.<xmlattr>.href";
  if (auto href = pt.get_optional<std::string>(path)) {
    sep::DeviceStatusLink link = {};
    link.href = href.value();
    sdev->device_status_link.emplace(link);
  }
  path = "SelfDevice.FileStatusLink.<xmlattr>.href";
  if (auto href = pt.get_optional<std::string>(path)) {
    sep::FileStatusLink link = {};
    link.href = href.value();
    sdev->file_status_link.emplace(link);
  }
  path = "SelfDevice.IPInterfaceListLink";
  if (auto child = pt.get_child_optional(path)) {
    auto href = child.value().get<std::string>("<xmlattr>.href", "");
    auto all = child.value().get<sep::UInt32>("<xmlattr>.all", 900);
    sep::IPInterfaceListLink link_list = {};
    link_list.href = href;
    link_list.all = all;
    sdev->ip_interface_list_link.emplace(link_list);
  }
  path = "SelfDevice.lFDI";
  if (auto lfdi = pt.get_optional<std::string>(path)) {
    auto hex = xml::util::Dehexify<sep::HexBinary160>(lfdi.value());
    sdev->lfdi.emplace(hex);
  }
  path = "SelfDevice.LoadShedAvailabilityListLink";
  if (auto child = pt.get_child_optional(path)) {
    auto href = child.value().get<std::string>("<xmlattr>.href", "");
    auto all = child.value().get<sep::UInt32>("<xmlattr>.all", 900);
    sep::LoadShedAvailabilityListLink link_list = {};
    link_list.href = href;
    link_list.all = all;
    sdev->load_shed_availability_list_link.emplace(link_list);
  }
  path = "SelfDevice.LogEventListLink";
  if (auto child = pt.get_child_optional(path)) {
    auto href = child.value().get<std::string>("<xmlattr>.href", "");
    auto all = child.value().get<sep::UInt32>("<xmlattr>.all", 900);
    sep::LogEventListLink link_list = {};
    link_list.href = href;
    link_list.all = all;
    sdev->log_event_list_link.emplace(link_list);
  }
  path = "SelfDevice.PowerStatusLink.<xmlattr>.href";
  if (auto href = pt.get_optional<std::string>(path)) {
    sep::PowerStatusLink link = {};
    link.href = href.value();
    sdev->power_status_link.emplace(link);
  }
};

void TreeMap(const sep::SelfDevice &sdev, boost::property_tree::ptree *pt) {
  std::string path = "SelfDevice.<xmlattr>.href";
  pt->put(path, sdev.href);
  path = "SelfDevice.<xmlattr>.pollRate";
  pt->put(path, sdev.poll_rate);
  path = "SelfDevice.<xmlattr>.subscribable";
  pt->put(path, xml::util::ToUnderlyingType(sdev.subscribable));
  path = "SelfDevice.sFDI";
  pt->put(path, sdev.sfdi);
  if (sdev.configuration_link.has_value()) {
    path = "SelfDevice.ConfigurationLink.<xmlattr>.href";
    pt->put(path, sdev.configuration_link.value().href);
  }
  if (sdev.der_list_link.has_value()) {
    path = "SelfDevice.DERListLink.<xmlattr>.href";
    pt->put(path, sdev.der_list_link.value().href);
    path = "SelfDevice.DERListLink.<xmlattr>.all";
    pt->put(path, sdev.der_list_link.value().all);
  }
  if (sdev.device_category.has_value()) {
    path = "SelfDevice.deviceCategory";
    auto category = xml::util::ToUnderlyingType(sdev.device_category.value());
    pt->put(path, xml::util::Hexify(category));
  }
  if (sdev.device_information_link.has_value()) {
    path = "SelfDevice.DeviceInformationLink.<xmlattr>.href";
    pt->put(path, sdev.device_information_link.value().href);
  }
  if (sdev.device_status_link.has_value()) {
    path = "SelfDevice.DeviceStatusLink.<xmlattr>.href";
    pt->put(path, sdev.device_status_link.value().href);
  }
  if (sdev.file_status_link.has_value()) {
    path = "SelfDevice.FileStatusLink.<xmlattr>.href";
    pt->put(path, sdev.file_status_link.value().href);
  }
  if (sdev.ip_interface_list_link.has_value()) {
    path = "SelfDevice.IPInterfaceListLink.<xmlattr>.href";
    pt->put(path, sdev.ip_interface_list_link.value().href);
    path = "SelfDevice.IPInterfaceListLink.<xmlattr>.all";
    pt->put(path, sdev.ip_interface_list_link.value().all);
  }
  if (sdev.lfdi.has_value()) {
    path = "SelfDevice.lFDI";
    pt->put(path, xml::util::Hexify(sdev.lfdi.value()));
  }
  if (sdev.load_shed_availability_list_link.has_value()) {
    path = "SelfDevice.LoadShedAvailabilityListLink.<xmlattr>.href";
    pt->put(path, sdev.load_shed_availability_list_link.value().href);
    path = "SelfDevice.LoadShedAvailabilityListLink.<xmlattr>.all";
    pt->put(path, sdev.load_shed_availability_list_link.value().all);
  }
  if (sdev.log_event_list_link.has_value()) {
    path = "SelfDevice.LogEventListLink.<xmlattr>.href";
    pt->put(path, sdev.log_event_list_link.value().href);
    path = "SelfDevice.LogEventListLink.<xmlattr>.all";
    pt->put(path, sdev.log_event_list_link.value().all);
  }
  if (sdev.power_status_link.has_value()) {
    path = "SelfDevice.PowerStatusLink.<xmlattr>.href";
    pt->put(path, sdev.power_status_link.value().href);
  }
};

std::string Serialize(const sep::SelfDevice &sdev) {
  boost::property_tree::ptree pt;
  TreeMap(sdev, &pt);

  xml::util::SetSchema(&pt);
  return xml::util::Stringify(&pt);
};

void Parse(const std::string &xml_str, sep::SelfDevice *sdev) {
  boost::property_tree::ptree pt = xml::util::Treeify(xml_str);
  ObjectMap(pt, sdev);
};

} // namespace xml
