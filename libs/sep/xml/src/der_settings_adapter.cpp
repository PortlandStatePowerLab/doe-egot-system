#include <boost/optional.hpp>
#include <sep/models/simple_types.hpp>
#include <sep/xml/device_capability_adapter.hpp>
#include <sep/xml/utilities.hpp>

namespace xml {
void ObjectMap(const boost::property_tree::ptree &pt, sep::DeviceCapability *dcap) {
  std::string path = "DeviceCapability.<xmlattr>.href";
  dcap->href = pt.get<std::string>(path);

  path = "DeviceCapability.CustomerAccountListLink";
  if (auto child = pt.get_child_optional(path)) {
    auto href = child.value().get<std::string>("<xmlattr>.href", "");
    auto all = child.value().get<sep::UInt32>("<xmlattr>.all", 900);
    sep::CustomerAccountListLink link_list = {};
    link_list.href = href;
    link_list.all = all;
    dcap->customer_account_list_link.emplace(link_list);
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
