#include "sep/models/der_control_type.hpp"
#include "sep/models/power_factor.hpp"
#include <boost/optional.hpp>
#include <sep/models/simple_types.hpp>
#include <sep/xml/der_capability_adapter.hpp>
#include <sep/xml/utilities.hpp>

namespace xml {
void ObjectMap(const boost::property_tree::ptree &pt,
               sep::DERCapability *dercap) {
  std::string path = "DERCapability.<xmlattr>.href";
  dercap->href = pt.get<std::string>(path);

  path = "DERCapability.modesSupported";
  dercap->modes_supported = static_cast<sep::DERControlType>(
      util::Dehexify<sep::HexBinary32>(pt.get<std::string>(path, "")));

  path = "DERCapability.type";
  dercap->type = static_cast<sep::DERType>(pt.get<sep::UInt8>(path, 0));

  path = "DERCapability.rtgMaxW.value";
  dercap->rtg_max_w.value = pt.get<sep::Int16>(path, 0);

  path = "DERCapability.rtgMaxW.multiplier";
  dercap->rtg_max_w.multiplier = pt.get<sep::Int8>(path, 0);

  path = "DERCapability.rtgAbnormalCategory";
  if (auto value = pt.get_optional<sep::UInt8>(path)) {
    auto object =
        static_cast<sep::DERCapability::AbnormalCategory>(value.value());
    dercap->rtg_abnormal_category.emplace(object);
  }

  path = "DERCapability.rtgMaxA";
  if (auto child = pt.get_child_optional(path)) {
    auto value = child.value().get<sep::Int16>("value", 0);
    auto multi = child.value().get<sep::Int8>("multiplier", 0);
    sep::CurrentRMS obj;
    obj.value = value;
    obj.multiplier = multi;
    dercap->rtg_max_a.emplace(obj);
  }

  path = "DERCapability.rtgMaxAh";
  if (auto child = pt.get_child_optional(path)) {
    auto value = child.value().get<sep::Int16>("value", 0);
    auto multi = child.value().get<sep::Int8>("multiplier", 0);
    sep::AmpereHour obj;
    obj.value = value;
    obj.multiplier = multi;
    dercap->rtg_max_ah.emplace(obj);
  }

  path = "DERCapability.rtgMaxChargeRateVA";
  if (auto child = pt.get_child_optional(path)) {
    auto value = child.value().get<sep::Int16>("value", 0);
    auto multi = child.value().get<sep::Int8>("multiplier", 0);
    sep::ApparentPower obj;
    obj.value = value;
    obj.multiplier = multi;
    dercap->rtg_max_charge_rate_va.emplace(obj);
  }

  path = "DERCapability.rtgMaxChargeRateW";
  if (auto child = pt.get_child_optional(path)) {
    auto value = child.value().get<sep::Int16>("value", 0);
    auto multi = child.value().get<sep::Int8>("multiplier", 0);
    sep::ActivePower obj;
    obj.value = value;
    obj.multiplier = multi;
    dercap->rtg_max_charge_rate_w.emplace(obj);
  }
  path = "DERCapability.rtgMaxDischargeRateW";
  if (auto child = pt.get_child_optional(path)) {
    auto value = child.value().get<sep::Int16>("value", 0);
    auto multi = child.value().get<sep::Int8>("multiplier", 0);
    sep::ActivePower obj;
    obj.value = value;
    obj.multiplier = multi;
    dercap->rtg_max_discharge_rate_w.emplace(obj);
  }
  path = "DERCapability.rtgMaxDischargeRateVA";
  if (auto child = pt.get_child_optional(path)) {
    auto value = child.value().get<sep::Int16>("value", 0);
    auto multi = child.value().get<sep::Int8>("multiplier", 0);
    sep::ApparentPower obj;
    obj.value = value;
    obj.multiplier = multi;
    dercap->rtg_max_discharge_rate_va.emplace(obj);
  }
  path = "DERCapability.rtgMaxVA";
  if (auto child = pt.get_child_optional(path)) {
    auto value = child.value().get<sep::Int16>("value", 0);
    auto multi = child.value().get<sep::Int8>("multiplier", 0);
    sep::ApparentPower obj;
    obj.value = value;
    obj.multiplier = multi;
    dercap->rtg_max_va.emplace(obj);
  }
  path = "DERCapability.rtgMaxVar";
  if (auto child = pt.get_child_optional(path)) {
    auto value = child.value().get<sep::Int16>("value", 0);
    auto multi = child.value().get<sep::Int8>("multiplier", 0);
    sep::ReactivePower obj;
    obj.value = value;
    obj.multiplier = multi;
    dercap->rtg_max_var.emplace(obj);
  }
  path = "DERCapability.rtgMaxVarNeg";
  if (auto child = pt.get_child_optional(path)) {
    auto value = child.value().get<sep::Int16>("value", 0);
    auto multi = child.value().get<sep::Int8>("multiplier", 0);
    sep::ReactivePower obj;
    obj.value = value;
    obj.multiplier = multi;
    dercap->rtg_max_var_neg.emplace(obj);
  }
  path = "DERCapability.rtgMaxWh";
  if (auto child = pt.get_child_optional(path)) {
    auto value = child.value().get<sep::Int16>("value", 0);
    auto multi = child.value().get<sep::Int8>("multiplier", 0);
    sep::WattHour obj;
    obj.value = value;
    obj.multiplier = multi;
    dercap->rtg_max_wh.emplace(obj);
  }
  path = "DERCapability.rtgMinPFOverExcited";
  if (auto child = pt.get_child_optional(path)) {
    auto value = child.value().get<sep::UInt16>("displacement", 0);
    auto multi = child.value().get<sep::Int8>("multiplier", 0);
    sep::PowerFactor obj;
    obj.displacement = value;
    obj.multiplier = multi;
    dercap->rtg_min_pf_over_excited.emplace(obj);
  }
  path = "DERCapability.rtgMinPFUnderExcited";
  if (auto child = pt.get_child_optional(path)) {
    auto value = child.value().get<sep::UInt16>("displacement", 0);
    auto multi = child.value().get<sep::Int8>("multiplier", 0);
    sep::PowerFactor obj;
    obj.displacement = value;
    obj.multiplier = multi;
    dercap->rtg_min_pf_under_excited.emplace(obj);
  }
  path = "DERCapability.rtgMinV";
  if (auto child = pt.get_child_optional(path)) {
    auto value = child.value().get<sep::Int16>("value", 0);
    auto multi = child.value().get<sep::Int8>("multiplier", 0);
    sep::VoltageRMS obj;
    obj.value = value;
    obj.multiplier = multi;
    dercap->rtg_max_v.emplace(obj);
  }
  path = "DERCapability.rtgNormalCategory";
  if (auto child = pt.get_child_optional(path)) {
    auto obj = static_cast<sep::DERCapability::NormalCategory>(
        pt.get<sep::UInt8>(path, 0));
    dercap->rtg_normal_category.emplace(obj);
  }
  path = "DERCapability.rtgOverExcitedPF";
  if (auto child = pt.get_child_optional(path)) {
    auto value = child.value().get<sep::UInt16>("displacement", 0);
    auto multi = child.value().get<sep::Int8>("multiplier", 0);
    sep::PowerFactor obj;
    obj.displacement = value;
    obj.multiplier = multi;
    dercap->rtg_over_excited_pf.emplace(obj);
  }
  path = "DERCapability.rtgOverExcitedW";
  if (auto child = pt.get_child_optional(path)) {
    auto value = child.value().get<sep::Int16>("value", 0);
    auto multi = child.value().get<sep::Int8>("multiplier", 0);
    sep::ActivePower obj;
    obj.value = value;
    obj.multiplier = multi;
    dercap->rtg_over_excited_w.emplace(obj);
  }
  path = "DERCapability.rtgUnderExcitedPF";
  if (auto child = pt.get_child_optional(path)) {
    auto value = child.value().get<sep::UInt16>("displacement", 0);
    auto multi = child.value().get<sep::Int8>("multiplier", 0);
    sep::PowerFactor obj;
    obj.displacement = value;
    obj.multiplier = multi;
    dercap->rtg_under_excited_pf.emplace(obj);
  }
  path = "DERCapability.rtgUnderExcitedW";
  if (auto child = pt.get_child_optional(path)) {
    auto value = child.value().get<sep::Int16>("value", 0);
    auto multi = child.value().get<sep::Int8>("multiplier", 0);
    sep::ActivePower obj;
    obj.value = value;
    obj.multiplier = multi;
    dercap->rtg_under_excited_w.emplace(obj);
  }
  path = "DERCapability.rtgVNom";
  if (auto child = pt.get_child_optional(path)) {
    auto value = child.value().get<sep::Int16>("value", 0);
    auto multi = child.value().get<sep::Int8>("multiplier", 0);
    sep::VoltageRMS obj;
    obj.value = value;
    obj.multiplier = multi;
    dercap->rtg_v_nom.emplace(obj);
  }
};

void TreeMap(const sep::DERCapability &dercap,
             boost::property_tree::ptree *pt) {
  std::string path = "DERCapability.<xmlattr>.href";
  pt->put(path, dercap.href);

  path = "DERCapability.modesSupported";
  pt->put(path, util::Hexify(util::ToUnderlyingType(dercap.modes_supported)));

  path = "DERCapability.rtgMaxW.value";
  pt->put(path, dercap.rtg_max_w.value);

  path = "DERCapability.rtgMaxW.multiplier";
  pt->put(path, dercap.rtg_max_w.multiplier);

  if (dercap.rtg_max_a.is_initialized()) {
    path = "DERCapability.rtgMaxA.value";
    pt->put(path, dercap.rtg_max_a.get().value);
    path = "DERCapability.rtgMaxA.multiplier";
    pt->put(path, dercap.rtg_max_a.get().multiplier);
  }

  if (dercap.rtg_max_ah.is_initialized()) {
    path = "DERCapability.rtgMaxAh.value";
    pt->put(path, dercap.rtg_max_ah.get().value);
    path = "DERCapability.rtgMaxAh.multiplier";
    pt->put(path, dercap.rtg_max_ah.get().multiplier);
  }

  if (dercap.rtg_max_charge_rate_va.is_initialized()) {
    path = "DERCapability.rtgMaxChargeRateVA.value";
    pt->put(path, dercap.rtg_max_charge_rate_va.get().value);
    path = "DERCapability.rtgMaxChargeRateVA.multiplier";
    pt->put(path, dercap.rtg_max_charge_rate_va.get().multiplier);
  }

  if (dercap.rtg_max_charge_rate_w.is_initialized()) {
    path = "DERCapability.rtgMaxChargeRateW.value";
    pt->put(path, dercap.rtg_max_charge_rate_w.get().value);
    path = "DERCapability.rtgMaxChargeRateW.multiplier";
    pt->put(path, dercap.rtg_max_charge_rate_w.get().multiplier);
  }

  if (dercap.rtg_max_discharge_rate_va.is_initialized()) {
    path = "DERCapability.rtgMaxDischargeRateVA.value";
    pt->put(path, dercap.rtg_max_discharge_rate_va.get().value);
    path = "DERCapability.rtgMaxDischargeRateVA.multiplier";
    pt->put(path, dercap.rtg_max_discharge_rate_va.get().multiplier);
  }

  if (dercap.rtg_max_discharge_rate_w.is_initialized()) {
    path = "DERCapability.rtgMaxDischargeRateW.value";
    pt->put(path, dercap.rtg_max_discharge_rate_w.get().value);
    path = "DERCapability.rtgMaxDischargeRateW.multiplier";
    pt->put(path, dercap.rtg_max_discharge_rate_w.get().multiplier);
  }

  if (dercap.rtg_max_v.is_initialized()) {
    path = "DERCapability.rtgMaxV.value";
    pt->put(path, dercap.rtg_max_v.get().value);
    path = "DERCapability.rtgMaxV.multiplier";
    pt->put(path, dercap.rtg_max_v.get().multiplier);
  }

  if (dercap.rtg_max_va.is_initialized()) {
    path = "DERCapability.rtgMaxVA.value";
    pt->put(path, dercap.rtg_max_va.get().value);
    path = "DERCapability.rtgMaxVA.multiplier";
    pt->put(path, dercap.rtg_max_va.get().multiplier);
  }

  if (dercap.rtg_max_var.is_initialized()) {
    path = "DERCapability.rtgMaxVar.value";
    pt->put(path, dercap.rtg_max_var.get().value);
    path = "DERCapability.rtgMaxVar.multiplier";
    pt->put(path, dercap.rtg_max_var.get().multiplier);
  }

  if (dercap.rtg_max_var_neg.is_initialized()) {
    path = "DERCapability.rtgMaxVarNeg.value";
    pt->put(path, dercap.rtg_max_var_neg.get().value);
    path = "DERCapability.rtgMaxVarNeg.multiplier";
    pt->put(path, dercap.rtg_max_var_neg.get().multiplier);
  }

  if (dercap.rtg_max_wh.is_initialized()) {
    path = "DERCapability.rtgMaxWh.value";
    pt->put(path, dercap.rtg_max_wh.get().value);
    path = "DERCapability.rtgMaxWh.multiplier";
    pt->put(path, dercap.rtg_max_wh.get().multiplier);
  }

  if (dercap.rtg_min_pf_over_excited.is_initialized()) {
    path = "DERCapability.rtgMinPFOverExcited.displacement";
    pt->put(path, dercap.rtg_min_pf_over_excited.get().displacement);
    path = "DERCapability.rtgMinPFOverExcited.multiplier";
    pt->put(path, dercap.rtg_min_pf_over_excited.get().multiplier);
  }

  if (dercap.rtg_min_pf_under_excited.is_initialized()) {
    path = "DERCapability.rtgMinPFUnderExcited.displacement";
    pt->put(path, dercap.rtg_min_pf_under_excited.get().displacement);
    path = "DERCapability.rtgMinPFUnderExcited.multiplier";
    pt->put(path, dercap.rtg_min_pf_under_excited.get().multiplier);
  }

  if (dercap.rtg_min_v.is_initialized()) {
    path = "DERCapability.rtgMinV.value";
    pt->put(path, dercap.rtg_min_v.get().value);
    path = "DERCapability.rtgMinV.multiplier";
    pt->put(path, dercap.rtg_min_v.get().multiplier);
  }

  if (dercap.rtg_normal_category.is_initialized()) {
    path = "DERCapability.rtgNormalCategory";
    pt->put(path, util::ToUnderlyingType(dercap.rtg_normal_category.get()));
  }

  if (dercap.rtg_over_excited_pf.is_initialized()) {
    path = "DERCapability.rtgOverExcitedPF.displacement";
    pt->put(path, dercap.rtg_over_excited_pf.get().displacement);
    path = "DERCapability.rtgOverExcitedPF.multiplier";
    pt->put(path, dercap.rtg_over_excited_pf.get().multiplier);
  }

  if (dercap.rtg_over_excited_w.is_initialized()) {
    path = "DERCapability.rtgOverExcitedW.value";
    pt->put(path, dercap.rtg_over_excited_w.get().value);
    path = "DERCapability.rtgOverExcitedW.multiplier";
    pt->put(path, dercap.rtg_over_excited_w.get().multiplier);
  }

  if (dercap.rtg_reactive_susceptance.is_initialized()) {
    path = "DERCapability.rtgReactiveSusceptance.value";
    pt->put(path, dercap.rtg_reactive_susceptance.get().value);
    path = "DERCapability.rtgReactiveSusceptance.multiplier";
    pt->put(path, dercap.rtg_reactive_susceptance.get().multiplier);
  }

  if (dercap.rtg_under_excited_w.is_initialized()) {
    path = "DERCapability.rtgUnderExcitedW.value";
    pt->put(path, dercap.rtg_under_excited_w.get().value);
    path = "DERCapability.rtgUnderExcitedW.multiplier";
    pt->put(path, dercap.rtg_under_excited_w.get().multiplier);
  }

  if (dercap.rtg_v_nom.is_initialized()) {
    path = "DERCapability.rtgVNom.value";
    pt->put(path, dercap.rtg_v_nom.get().value);
    path = "DERCapability.rtgVNom.multiplier";
    pt->put(path, dercap.rtg_v_nom.get().multiplier);
  }
};

std::string Serialize(const sep::DERCapability &dercap) {
  boost::property_tree::ptree pt;
  TreeMap(dercap, &pt);

  xml::util::SetSchema(&pt);
  return xml::util::Stringify(&pt);
}

void Parse(const std::string &xml_str, sep::DERCapability *dercap) {
  boost::property_tree::ptree pt = xml::util::Treeify(xml_str);
  ObjectMap(pt, dercap);
}
} // namespace xml
