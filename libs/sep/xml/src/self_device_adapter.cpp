#include <boost/foreach.hpp>
#include <sep/xml/self_device_adapter.hpp>
#include <sep/xml/utilities.hpp>

namespace xml {
void ObjectMap(const boost::property_tree::ptree &pt, sep::SelfDevice *sdev) {
  std::string path = "SelfDevice.<xmlattr>.pollRate";
  sdev->poll_rate = pt.get<sep::UInt32>(path, 900);
  path = "SelfDevice.sFDI";
  sdev->sfdi = pt.get<sep::SFDIType>(path, 0);
  path = "SelfDevice.<xmlattr>.subscribable";
  sdev->subscribable = static_cast<sep::SubscribableType>(pt.get<sep::UInt8>(path, 0));
  path = "SelfDevice.ConfigurationLink.<xmlattr>.href";
  if (auto href = pt.get_optional<std::string>(path)) {
    sdev->configuration_link.value().href = href.value();
  }
  path = "SelfDevice.DERListLink.<xmlattr>.href";
  if (auto href = pt.get_optional<std::string>(path)) {
    sdev->der_list_link.value().href = href.value();
  }
  path = "SelfDevice.DERListLink.<xmlattr>.all";
  if (auto all = pt.get_optional<sep::UInt32>(path)) {
    sdev->der_list_link.value().all = all.value();
  }
  path = "SelfDevice.deviceCategory";
  if (auto device_category = pt.get_optional<sep::HexBinary32>(path)) {
    sdev->device_category.value() =
        static_cast<sep::DeviceCategoryType>(device_category.value());
  }
  path = "SelfDevice.DeviceInformationLink.<xmlattr>.href";
  if (auto href = pt.get_optional<std::string>(path)) {
    sdev->device_information_link.value().href = href.value();
  }
  path = "SelfDevice.DeviceStatusLink.<xmlattr>.href";
  if (auto href = pt.get_optional<std::string>(path)) {
    sdev->device_status_link.value().href = href.value();
  }
  path = "SelfDevice.FileStatusLink.<xmlattr>.href";
  if (auto href = pt.get_optional<std::string>(path)) {
    sdev->file_status_link.value().href = href.value();
  }
  path = "SelfDevice.IPInterfaceListLink.<xmlattr>.href";
  if (auto href = pt.get_optional<std::string>(path)) {
    sdev->ip_interface_list_link.value().href = href.value();
  }
  path = "SelfDevice.IPInterfaceListLink.<xmlattr>.all";
  if (auto all = pt.get_optional<sep::UInt32>(path)) {
    sdev->ip_interface_list_link.value().all = all.value();
  }
  // path = "SelfDevice.lFDI";
  // if (auto lfdi = pt.get_optional<std::string>(path)) {
  //   sdev->lfdi.value() =
  //   xml::util::Dehexify<sep::HexBinary160>(lfdi.value());
  // }
  path = "SelfDevice.lFDI";
  if (auto lfdi = pt.get_optional<sep::HexBinary160>(path)) {
    sdev->lfdi.value() = lfdi.value();
  }
  path = "SelfDevice.LoadShedAvailabilityListLink.<xmlattr>.href";
  if (auto href = pt.get_optional<std::string>(path)) {
    sdev->load_shed_availability_list_link.value().href = href.value();
  }
  path = "SelfDevice.LoadShedAvailabilityListLink.<xmlattr>.all";
  if (auto all = pt.get_optional<sep::UInt32>(path)) {
    sdev->load_shed_availability_list_link.value().all = all.value();
  }
  path = "SelfDevice.LogEventListLink.<xmlattr>.href";
  if (auto href = pt.get_optional<std::string>(path)) {
    sdev->log_event_list_link.value().href = href.value();
  }
  path = "SelfDevice.LogEventListLink.<xmlattr>.all";
  if (auto all = pt.get_optional<sep::UInt32>(path)) {
    sdev->log_event_list_link.value().all = all.value();
  }
  path = "SelfDevice.PowerStatusLink.<xmlattr>.href";
  if (auto href = pt.get_optional<std::string>(path)) {
    sdev->power_status_link.value().href = href.value();
  }
};

void TreeMap(const sep::SelfDevice &sdev, boost::property_tree::ptree *pt) {
  pt->put("SelfDevice.<xmlattr>.href", sdev.href);
  pt->put("SelfDevice.<xmlattr>.pollRate", sdev.poll_rate);
  pt->put("SelfDevice.<xmlattr>.subscribable",
          xml::util::ToUnderlyingType(sdev.subscribable));
  pt->put("SelfDevice.sFDI", sdev.sfdi);
  std::string path;
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
    pt->put(path, xml::util::Hexify(xml::util::ToUnderlyingType(
                      sdev.device_category.value())));
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
