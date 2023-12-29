#include <boost/optional.hpp>
#include <sep/models/simple_types.hpp>
#include <sep/xml/device_capability_adapter.hpp>
#include <sep/xml/utilities.hpp>

namespace xml {
void ObjectMap(const boost::property_tree::ptree &pt,
               sep::DeviceCapability *dcap) {
  std::string path = "DeviceCapability.<xmlattr>.href";
  dcap->href = pt.get<std::string>(path);

  path = "DeviceCapability.<xmlattr>.pollRate";
  dcap->poll_rate = pt.get<sep::UInt32>(path);

  path = "DeviceCapability.CustomerAccountListLink";
  if (auto child = pt.get_child_optional(path)) {
    auto href = child.value().get<std::string>("<xmlattr>.href", "");
    auto all = child.value().get<sep::UInt32>("<xmlattr>.all", 900);
    sep::CustomerAccountListLink link_list = {};
    link_list.href = href;
    link_list.all = all;
    dcap->customer_account_list_link.emplace(link_list);
  }
  path = "DeviceCapability.DemandResponseProgramListLink";
  if (auto child = pt.get_child_optional(path)) {
    auto href = child.value().get<std::string>("<xmlattr>.href", "");
    auto all = child.value().get<sep::UInt32>("<xmlattr>.all", 900);
    sep::DemandResponseProgramListLink link_list = {};
    link_list.href = href;
    link_list.all = all;
    dcap->demand_response_program_list_link.emplace(link_list);
  }
  path = "DeviceCapability.DERProgramListLink";
  if (auto child = pt.get_child_optional(path)) {
    auto href = child.value().get<std::string>("<xmlattr>.href", "");
    auto all = child.value().get<sep::UInt32>("<xmlattr>.all", 900);
    sep::DERProgramListLink link_list = {};
    link_list.href = href;
    link_list.all = all;
    dcap->der_program_list_link.emplace(link_list);
  }
  path = "DeviceCapability.FileListLink";
  if (auto child = pt.get_child_optional(path)) {
    auto href = child.value().get<std::string>("<xmlattr>.href", "");
    auto all = child.value().get<sep::UInt32>("<xmlattr>.all", 900);
    sep::FileListLink link_list = {};
    link_list.href = href;
    link_list.all = all;
    dcap->file_list_link.emplace(link_list);
  }
  path = "DeviceCapability.MessagingProgramListLink";
  if (auto child = pt.get_child_optional(path)) {
    auto href = child.value().get<std::string>("<xmlattr>.href", "");
    auto all = child.value().get<sep::UInt32>("<xmlattr>.all", 900);
    sep::MessagingProgramListLink link_list = {};
    link_list.href = href;
    link_list.all = all;
    dcap->messaging_program_list_link.emplace(link_list);
  }
  path = "DeviceCapability.PrepaymentListLink";
  if (auto child = pt.get_child_optional(path)) {
    auto href = child.value().get<std::string>("<xmlattr>.href", "");
    auto all = child.value().get<sep::UInt32>("<xmlattr>.all", 900);
    sep::PrepaymentListLink link_list = {};
    link_list.href = href;
    link_list.all = all;
    dcap->prepayment_list_link.emplace(link_list);
  }
  path = "DeviceCapability.ResponseSetListLink";
  if (auto child = pt.get_child_optional(path)) {
    auto href = child.value().get<std::string>("<xmlattr>.href", "");
    auto all = child.value().get<sep::UInt32>("<xmlattr>.all", 900);
    sep::ResponseSetListLink link_list = {};
    link_list.href = href;
    link_list.all = all;
    dcap->response_set_list_link.emplace(link_list);
  }
  path = "DeviceCapability.TariffProfileListLink";
  if (auto child = pt.get_child_optional(path)) {
    auto href = child.value().get<std::string>("<xmlattr>.href", "");
    auto all = child.value().get<sep::UInt32>("<xmlattr>.all", 900);
    sep::TariffProfileListLink link_list = {};
    link_list.href = href;
    link_list.all = all;
    dcap->tariff_profile_list_link.emplace(link_list);
  }
  path = "DeviceCapability.TimeLink.<xmlattr>.href";
  if (auto href = pt.get_optional<std::string>(path)) {
    sep::TimeLink link = {};
    link.href = href.value();
    dcap->time_link.emplace(link);
  }
  path = "DeviceCapability.UsagePointListLink";
  if (auto child = pt.get_child_optional(path)) {
    auto href = child.value().get<std::string>("<xmlattr>.href", "");
    auto all = child.value().get<sep::UInt32>("<xmlattr>.all", 900);
    sep::UsagePointListLink link_list = {};
    link_list.href = href;
    link_list.all = all;
    dcap->usage_point_list_link.emplace(link_list);
  }
  path = "DeviceCapability.EndDeviceListLink";
  if (auto child = pt.get_child_optional(path)) {
    auto href = child.value().get<std::string>("<xmlattr>.href", "");
    auto all = child.value().get<sep::UInt32>("<xmlattr>.all", 900);
    sep::EndDeviceListLink link_list = {};
    link_list.href = href;
    link_list.all = all;
    dcap->end_device_list_link.emplace(link_list);
  }
  path = "DeviceCapability.MirrorUsagePointListLink";
  if (auto child = pt.get_child_optional(path)) {
    auto href = child.value().get<std::string>("<xmlattr>.href", "");
    auto all = child.value().get<sep::UInt32>("<xmlattr>.all", 900);
    sep::MirrorUsagePointListLink link_list = {};
    link_list.href = href;
    link_list.all = all;
    dcap->mirror_usage_point_list_link.emplace(link_list);
  }
  path = "DeviceCapability.SelfDeviceLink.<xmlattr>.href";
  if (auto href = pt.get_optional<std::string>(path)) {
    sep::SelfDeviceLink link = {};
    link.href = href.value();
    dcap->self_device_link.emplace(link);
  }
};

void TreeMap(const sep::DeviceCapability &dcap,
             boost::property_tree::ptree *pt) {
  std::string path = "DeviceCapability.<xmlattr>.href";
  pt->put(path, dcap.href);

  path = "DeviceCapability.<xmlattr>.pollRate";
  pt->put(path, dcap.poll_rate);

  if (dcap.customer_account_list_link.is_initialized()) {
    path = "DeviceCapability.CustomerAccountListLink.<xmlattr>.href";
    pt->put(path, dcap.customer_account_list_link.get().href);
    path = "DeviceCapability.CustomerAccountListLink.<xmlattr>.all";
    pt->put(path, dcap.customer_account_list_link.get().all);
  }
  if (dcap.demand_response_program_list_link.is_initialized()) {
    path = "DeviceCapability.DemandResponseProgramListLink.<xmlattr>.href";
    pt->put(path, dcap.demand_response_program_list_link.get().href);
    path = "DeviceCapability.DemandResponseProgramListLink.<xmlattr>.all";
    pt->put(path, dcap.demand_response_program_list_link.get().all);
  }
  if (dcap.der_program_list_link.is_initialized()) {
    path = "DeviceCapability.DERProgramListLink.<xmlattr>.href";
    pt->put(path, dcap.der_program_list_link.get().href);
    path = "DeviceCapability.DERProgramListLink.<xmlattr>.all";
    pt->put(path, dcap.der_program_list_link.get().all);
  }
  if (dcap.file_list_link.is_initialized()) {
    path = "DeviceCapability.FileListLink.<xmlattr>.href";
    pt->put(path, dcap.file_list_link.get().href);
    path = "DeviceCapability.FileListLink.<xmlattr>.all";
    pt->put(path, dcap.file_list_link.get().all);
  }
  if (dcap.messaging_program_list_link.is_initialized()) {
    path = "DeviceCapability.MessagingProgramListLink.<xmlattr>.href";
    pt->put(path, dcap.messaging_program_list_link.get().href);
    path = "DeviceCapability.MessagingProgramListLink.<xmlattr>.all";
    pt->put(path, dcap.messaging_program_list_link.get().all);
  }
  if (dcap.prepayment_list_link.is_initialized()) {
    path = "DeviceCapability.PrepaymentListLink.<xmlattr>.href";
    pt->put(path, dcap.prepayment_list_link.get().href);
    path = "DeviceCapability.PrepaymentListLink.<xmlattr>.all";
    pt->put(path, dcap.prepayment_list_link.get().all);
  }
  if (dcap.response_set_list_link.is_initialized()) {
    path = "DeviceCapability.ResponseSetListLink.<xmlattr>.href";
    pt->put(path, dcap.response_set_list_link.get().href);
    path = "DeviceCapability.ResponseSetListLink.<xmlattr>.all";
    pt->put(path, dcap.response_set_list_link.get().all);
  }
  if (dcap.tariff_profile_list_link.is_initialized()) {
    path = "DeviceCapability.TariffProfileListLink.<xmlattr>.href";
    pt->put(path, dcap.tariff_profile_list_link.get().href);
    path = "DeviceCapability.TariffProfileListLink.<xmlattr>.all";
    pt->put(path, dcap.tariff_profile_list_link.get().all);
  }
  if (dcap.time_link.is_initialized()) {
    path = "DeviceCapability.TimeLink.<xmlattr>.href";
    pt->put(path, dcap.time_link.get().href);
  }
  if (dcap.usage_point_list_link.is_initialized()) {
    path = "DeviceCapability.UsagePointListLink.<xmlattr>.href";
    pt->put(path, dcap.usage_point_list_link.get().href);
    path = "DeviceCapability.UsagePointListLink.<xmlattr>.all";
    pt->put(path, dcap.usage_point_list_link.get().all);
  }
  if (dcap.end_device_list_link.is_initialized()) {
    path = "DeviceCapability.EndDeviceListLink.<xmlattr>.href";
    pt->put(path, dcap.end_device_list_link.get().href);
    path = "DeviceCapability.EndDeviceListLink.<xmlattr>.all";
    pt->put(path, dcap.end_device_list_link.get().all);
  }
  if (dcap.mirror_usage_point_list_link.is_initialized()) {
    path = "DeviceCapability.MirrorUsagePointListLink.<xmlattr>.href";
    pt->put(path, dcap.mirror_usage_point_list_link.get().href);
    path = "DeviceCapability.MirrorUsagePointListLink.<xmlattr>.all";
    pt->put(path, dcap.mirror_usage_point_list_link.get().all);
  }
  if (dcap.self_device_link.is_initialized()) {
    path = "DeviceCapability.SelfDeviceLink.<xmlattr>.href";
    pt->put(path, dcap.self_device_link.get().href);
  }
};

std::string Serialize(const sep::DeviceCapability &dcap) {
  boost::property_tree::ptree pt;
  TreeMap(dcap, &pt);

  xml::util::SetSchema(&pt);
  return xml::util::Stringify(&pt);
}

void Parse(const std::string &xml_str, sep::DeviceCapability *dcap) {
  boost::property_tree::ptree pt = xml::util::Treeify(xml_str);
  ObjectMap(pt, dcap);
}
} // namespace xml
