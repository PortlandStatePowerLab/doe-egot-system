
#include "sep/models/der_availability.hpp"
#include "sep/models/der_capability.hpp"
#include <sep/xml/der_adapter.hpp>
#include <sep/xml/utilities.hpp>

namespace xml {
void ObjectMap(const boost::property_tree::ptree &pt, sep::DER *der) {
  std::string path = "DER.<xmlattr>.href";
  der->href = pt.get<std::string>(path, "");

  path = "DER.<xmlattr>.subscribable";
  der->subscribable =
      static_cast<sep::SubscribableType>(pt.get<sep::UInt8>(path, 0));

  path = "DER.AssociatedDERProgramListLink";
  if (auto child = pt.get_child_optional(path)) {
    auto href = child.value().get<std::string>("<xmlattr>.href", "");
    auto all = child.value().get<sep::UInt32>("<xmlattr>.all", 900);
    sep::AssociatedDERProgramListLink list_link = {};
    list_link.href = href;
    list_link.all = all;

    der->associated_der_program_list_link.emplace(list_link);
  }

  path = "DER.AssociatedUsagePointLink.<xmlattr>.href";
  if (auto link = pt.get_optional<std::string>(path)) {
    sep::AssociatedUsagePointLink object;
    object.href = link.value();
    der->associated_usage_program_link.emplace(object);
  }

  path = "DER.CurrentDERProgramLink.<xmlattr>.href";
  if (auto link = pt.get_optional<std::string>(path)) {
    sep::CurrentDERProgramLink object;
    object.href = link.value();
    der->current_der_program_link.emplace(object);
  }

  path = "DER.DERAvailabilityLink.<xmlattr>.href";
  if (auto link = pt.get_optional<std::string>(path)) {
    sep::DERAvailabilityLink object;
    object.href = link.value();
    der->der_availability_link.emplace(object);
  }

  path = "DER.DERCapabilityLink.<xmlattr>.href";
  if (auto link = pt.get_optional<std::string>(path)) {
    sep::DERCapabilityLink object;
    object.href = link.value();
    der->der_capability_link.emplace(object);
  }

  path = "DER.DERSettingsLink.<xmlattr>.href";
  if (auto link = pt.get_optional<std::string>(path)) {
    sep::DERSettingsLink object;
    object.href = link.value();
    der->der_settings_link.emplace(object);
  }

  path = "DER.DERStatusLink.<xmlattr>.href";
  if (auto link = pt.get_optional<std::string>(path)) {
    sep::DERStatusLink object;
    object.href = link.value();
    der->der_status_link.emplace(object);
  }
};

void TreeMap(const sep::DER &der, boost::property_tree::ptree *pt) {
  std::string path = "DER.<xmlattr>.href";
  pt->put(path, der.href);
  path = "DER.<xmlattr>.subscribable";
  pt->put(path, util::ToUnderlyingType(der.subscribable));
  if (der.associated_der_program_list_link.is_initialized()) {
    path = "DER.AssociatedDERProgramListLink.<xmlattr>.href";
    pt->put(path, der.associated_der_program_list_link.get().href);
    path = "DER.AssociatedDERProgramListLink.<xmlattr>.all";
    pt->put(path, der.associated_der_program_list_link.get().all);
  }

  if (der.associated_usage_program_link.is_initialized()) {
    path = "DER.AssociatedUsagePointLink.<xmlattr>.href";
    pt->put(path, der.associated_usage_program_link.value().href);
  }

  if (der.current_der_program_link.is_initialized()) {
    path = "DER.CurrentDERProgramLink.<xmlattr>.href";
    pt->put(path, der.current_der_program_link.value().href);
  }

  if (der.der_availability_link.is_initialized()) {
    path = "DER.DERAvailabilityLink.<xmlattr>.href";
    pt->put(path, der.der_availability_link.value().href);
  }

  if (der.der_capability_link.is_initialized()) {
    path = "DER.DERCapabilityLink.<xmlattr>.href";
    pt->put(path, der.der_capability_link.value().href);
  }

  if (der.der_settings_link.is_initialized()) {
    path = "DER.DERSettingsLink.<xmlattr>.href";
    pt->put(path, der.der_settings_link.value().href);
  }

  if (der.der_status_link.is_initialized()) {
    path = "DER.DERStatusLink.<xmlattr>.href";
    pt->put(path, der.der_status_link.value().href);
  }
};

std::string Serialize(const sep::DER &der) {
  boost::property_tree::ptree pt;
  TreeMap(der, &pt);

  xml::util::SetSchema(&pt);
  return xml::util::Stringify(&pt);
};

void Parse(const std::string &xml_str, sep::DER *der) {
  boost::property_tree::ptree pt = xml::util::Treeify(xml_str);
  ObjectMap(pt, der);
};
} // namespace xml
