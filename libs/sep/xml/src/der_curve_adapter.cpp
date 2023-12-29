#include "sep/models/der_curve.hpp"
#include "sep/models/der_curve_type.hpp"
#include <boost/optional.hpp>
#include <sep/models/simple_types.hpp>
#include <sep/xml/device_capability_adapter.hpp>
#include <sep/xml/utilities.hpp>

namespace xml {
void ObjectMap(const boost::property_tree::ptree &pt, sep::DERCurve *dc) {
  std::string path = "DERCurve.<xmlattr>.href";
  dc->href = pt.get<std::string>(path);

  path = "DERCurve.mRID";
  dc->mrid = pt.get<sep::mRIDType>(path);

  path = "DERCurve.creationTime";
  dc->creation_time = pt.get<sep::TimeType>(path, 0);

  path = "DERCurve.curveType";
  dc->curve_type = static_cast<sep::DERCurveType>(pt.get<sep::UInt8>(path, 0));

  path = "DERCurve.CurveData";
  dc->creation_time = pt.get<sep::TimeType>(path, 0);

  path = "DERCurve.description";
  if (auto child = pt.get_child_optional(path)) {
    dc->description = child.value().get<sep::String32>(path, "");
  }

  path = "DERCurve.version";
  if (auto child = pt.get_child_optional(path)) {
    dc->version = child.value().get<sep::VersionType>(path, false);
  }

  path = "DERCurve.autonomousVRefEnable";
  if (auto child = pt.get_child_optional(path)) {
    dc->autonomous_vref_enable = child.value().get<bool>(path, false);
  }

  path = "DERCurve.autonomousVRefTimeConstant";
  if (auto child = pt.get_child_optional(path)) {
    dc->autonomous_vref_time_constant = child.value().get<bool>(path, false);
  }
};

void TreeMap(const sep::DERCurve &dcap, boost::property_tree::ptree *pt) {
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

std::string Serialize(const sep::DERCurve &dcap) {
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
