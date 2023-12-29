
#include "sep/models/der_control_type.hpp"
#include "sep/models/power_factor.hpp"
#include "sep/models/subscribable_type.hpp"
#include <boost/optional.hpp>
#include <sep/models/simple_types.hpp>
#include <sep/xml/der_settings_adapter.hpp>
#include <sep/xml/utilities.hpp>

namespace xml {
void ObjectMap(const boost::property_tree::ptree &pt, sep::DERSettings *derg) {
  std::string path = "DERSettings.<xmlattr>.href";
  derg->href = pt.get<std::string>(path);

  path = "DERSettings.<xmlatter>.subscribable";
  derg->subscribable =
      static_cast<sep::SubscribableType>(pt.get<sep::UInt8>(path, 0));

  path = "DERSettings.setMaxW.value";
  derg->set_max_w.value = pt.get<sep::Int16>(path, 0);
  path = "DERSettings.setMaxW.multiplier";
  derg->set_max_w.multiplier = pt.get<sep::Int8>(path, 0);

  path = "DERSettings.setGradW.multiplier";
  derg->set_gradrw = pt.get<sep::UInt16>(path, 0);

  path = "DERSettings.updatedTime";
  derg->updated_time = pt.get<sep::TimeType>(path, 0);

  path = "DERSettings.modesEnabled";
  if (auto value = pt.get_optional<std::string>(path)) {
    derg->modes_enabled = static_cast<sep::DERControlType>(
        util::Dehexify<sep::HexBinary32>(value.value()));
  }

  path = "DERSettings.setMaxA";
  if (auto child = pt.get_child_optional(path)) {
    auto value = child.value().get<sep::Int16>("value", 0);
    auto multi = child.value().get<sep::Int8>("multiplier", 0);
    sep::CurrentRMS obj;
    obj.value = value;
    obj.multiplier = multi;
    derg->set_max_a.emplace(obj);
  }

  path = "DERSettings.setMaxAh";
  if (auto child = pt.get_child_optional(path)) {
    auto value = child.value().get<sep::Int16>("value", 0);
    auto multi = child.value().get<sep::Int8>("multiplier", 0);
    sep::AmpereHour obj;
    obj.value = value;
    obj.multiplier = multi;
    derg->set_max_ah.emplace(obj);
  }

  path = "DERSettings.setMaxChargeRateVA";
  if (auto child = pt.get_child_optional(path)) {
    auto value = child.value().get<sep::Int16>("value", 0);
    auto multi = child.value().get<sep::Int8>("multiplier", 0);
    sep::ApparentPower obj;
    obj.value = value;
    obj.multiplier = multi;
    derg->set_max_charge_rate_va.emplace(obj);
  }

  path = "DERSettings.setMaxChargeRateW";
  if (auto child = pt.get_child_optional(path)) {
    auto value = child.value().get<sep::Int16>("value", 0);
    auto multi = child.value().get<sep::Int8>("multiplier", 0);
    sep::ActivePower obj;
    obj.value = value;
    obj.multiplier = multi;
    derg->set_max_charge_rate_w.emplace(obj);
  }

  path = "DERSettings.setMaxDischargeRateW";
  if (auto child = pt.get_child_optional(path)) {
    auto value = child.value().get<sep::Int16>("value", 0);
    auto multi = child.value().get<sep::Int8>("multiplier", 0);
    sep::ActivePower obj;
    obj.value = value;
    obj.multiplier = multi;
    derg->set_max_discharge_rate_w.emplace(obj);
  }
  path = "DERSettings.setMaxDischargeRateVA";
  if (auto child = pt.get_child_optional(path)) {
    auto value = child.value().get<sep::Int16>("value", 0);
    auto multi = child.value().get<sep::Int8>("multiplier", 0);
    sep::ApparentPower obj;
    obj.value = value;
    obj.multiplier = multi;
    derg->set_max_discharge_rate_va.emplace(obj);
  }
  path = "DERSettings.setMaxVA";
  if (auto child = pt.get_child_optional(path)) {
    auto value = child.value().get<sep::Int16>("value", 0);
    auto multi = child.value().get<sep::Int8>("multiplier", 0);
    sep::ApparentPower obj;
    obj.value = value;
    obj.multiplier = multi;
    derg->set_max_va.emplace(obj);
  }
  path = "DERSettings.setMaxVar";
  if (auto child = pt.get_child_optional(path)) {
    auto value = child.value().get<sep::Int16>("value", 0);
    auto multi = child.value().get<sep::Int8>("multiplier", 0);
    sep::ReactivePower obj;
    obj.value = value;
    obj.multiplier = multi;
    derg->set_max_var.emplace(obj);
  }
  path = "DERSettings.setMaxVarNeg";
  if (auto child = pt.get_child_optional(path)) {
    auto value = child.value().get<sep::Int16>("value", 0);
    auto multi = child.value().get<sep::Int8>("multiplier", 0);
    sep::ReactivePower obj;
    obj.value = value;
    obj.multiplier = multi;
    derg->set_max_var_neg.emplace(obj);
  }
  path = "DERSettings.setMaxWh";
  if (auto child = pt.get_child_optional(path)) {
    auto value = child.value().get<sep::Int16>("value", 0);
    auto multi = child.value().get<sep::Int8>("multiplier", 0);
    sep::WattHour obj;
    obj.value = value;
    obj.multiplier = multi;
    derg->set_max_wh.emplace(obj);
  }
  path = "DERSettings.setMinPFOverExcited";
  if (auto child = pt.get_child_optional(path)) {
    auto value = child.value().get<sep::UInt16>("displacement", 0);
    auto multi = child.value().get<sep::Int8>("multiplier", 0);
    sep::PowerFactor obj;
    obj.displacement = value;
    obj.multiplier = multi;
    derg->set_min_pf_over_excited.emplace(obj);
  }

  path = "DERSettings.setMinV";
  if (auto child = pt.get_child_optional(path)) {
    auto value = child.value().get<sep::Int16>("value", 0);
    auto multi = child.value().get<sep::Int8>("multiplier", 0);
    sep::VoltageRMS obj;
    obj.value = value;
    obj.multiplier = multi;
    derg->set_max_v.emplace(obj);
  }
  path = "DERSettings.setSoftGradW";
  if (auto opt = pt.get_optional<sep::UInt16>(path)) {
    derg->set_soft_grad_w.emplace(opt.value());
  }

  path = "DERSettings.setVNom";
  if (auto child = pt.get_child_optional(path)) {
    auto value = child.value().get<sep::Int16>("value", 0);
    auto multi = child.value().get<sep::Int8>("multiplier", 0);
    sep::VoltageRMS obj;
    obj.value = value;
    obj.multiplier = multi;
    derg->set_v_nom.emplace(obj);
  }

  path = "DERSettings.setVRef";
  if (auto child = pt.get_child_optional(path)) {
    auto value = child.value().get<sep::Int16>("value", 0);
    auto multi = child.value().get<sep::Int8>("multiplier", 0);
    sep::VoltageRMS obj;
    obj.value = value;
    obj.multiplier = multi;
    derg->set_v_ref.emplace(obj);
  }

  path = "DERSettings.setVRefOfs";
  if (auto child = pt.get_child_optional(path)) {
    auto value = child.value().get<sep::Int16>("value", 0);
    auto multi = child.value().get<sep::Int8>("multiplier", 0);
    sep::VoltageRMS obj;
    obj.value = value;
    obj.multiplier = multi;
    derg->set_v_ref_ofs.emplace(obj);
  }
};

void TreeMap(const sep::DERSettings &derg, boost::property_tree::ptree *pt) {
  std::string path = "DERSettings.<xmlattr>.href";
  pt->put(path, derg.href);

  path = "DERSettings.modesSupported";
  pt->put(path, util::Hexify(util::ToUnderlyingType(derg.modes_enabled)));

  path = "DERSettings.setMaxW.value";
  pt->put(path, derg.set_max_w.value);

  path = "DERSettings.setMaxW.multiplier";
  pt->put(path, derg.set_max_w.multiplier);

  if (derg.set_max_a.is_initialized()) {
    path = "DERSettings.setMaxA.value";
    pt->put(path, derg.set_max_a.get().value);
    path = "DERSettings.setMaxA.multiplier";
    pt->put(path, derg.set_max_a.get().multiplier);
  }

  if (derg.set_max_ah.is_initialized()) {
    path = "DERSettings.setMaxAh.value";
    pt->put(path, derg.set_max_ah.get().value);
    path = "DERSettings.setMaxAh.multiplier";
    pt->put(path, derg.set_max_ah.get().multiplier);
  }

  if (derg.set_max_charge_rate_va.is_initialized()) {
    path = "DERSettings.setMaxChargeRateVA.value";
    pt->put(path, derg.set_max_charge_rate_va.get().value);
    path = "DERSettings.setMaxChargeRateVA.multiplier";
    pt->put(path, derg.set_max_charge_rate_va.get().multiplier);
  }

  if (derg.set_max_charge_rate_w.is_initialized()) {
    path = "DERSettings.setMaxChargeRateW.value";
    pt->put(path, derg.set_max_charge_rate_w.get().value);
    path = "DERSettings.setMaxChargeRateW.multiplier";
    pt->put(path, derg.set_max_charge_rate_w.get().multiplier);
  }

  if (derg.set_max_discharge_rate_va.is_initialized()) {
    path = "DERSettings.setMaxDischargeRateVA.value";
    pt->put(path, derg.set_max_discharge_rate_va.get().value);
    path = "DERSettings.setMaxDischargeRateVA.multiplier";
    pt->put(path, derg.set_max_discharge_rate_va.get().multiplier);
  }

  if (derg.set_max_discharge_rate_w.is_initialized()) {
    path = "DERSettings.setMaxDischargeRateW.value";
    pt->put(path, derg.set_max_discharge_rate_w.get().value);
    path = "DERSettings.setMaxDischargeRateW.multiplier";
    pt->put(path, derg.set_max_discharge_rate_w.get().multiplier);
  }

  if (derg.set_max_v.is_initialized()) {
    path = "DERSettings.setMaxV.value";
    pt->put(path, derg.set_max_v.get().value);
    path = "DERSettings.setMaxV.multiplier";
    pt->put(path, derg.set_max_v.get().multiplier);
  }

  if (derg.set_max_va.is_initialized()) {
    path = "DERSettings.setMaxVA.value";
    pt->put(path, derg.set_max_va.get().value);
    path = "DERSettings.setMaxVA.multiplier";
    pt->put(path, derg.set_max_va.get().multiplier);
  }

  if (derg.set_max_var.is_initialized()) {
    path = "DERSettings.setMaxVar.value";
    pt->put(path, derg.set_max_var.get().value);
    path = "DERSettings.setMaxVar.multiplier";
    pt->put(path, derg.set_max_var.get().multiplier);
  }

  if (derg.set_max_var_neg.is_initialized()) {
    path = "DERSettings.setMaxVarNeg.value";
    pt->put(path, derg.set_max_var_neg.get().value);
    path = "DERSettings.setMaxVarNeg.multiplier";
    pt->put(path, derg.set_max_var_neg.get().multiplier);
  }

  if (derg.set_max_wh.is_initialized()) {
    path = "DERSettings.setMaxWh.value";
    pt->put(path, derg.set_max_wh.get().value);
    path = "DERSettings.setMaxWh.multiplier";
    pt->put(path, derg.set_max_wh.get().multiplier);
  }

  if (derg.set_min_pf_over_excited.is_initialized()) {
    path = "DERSettings.setMinPFOverExcited.displacement";
    pt->put(path, derg.set_min_pf_over_excited.get().displacement);
    path = "DERSettings.setMinPFOverExcited.multiplier";
    pt->put(path, derg.set_min_pf_over_excited.get().multiplier);
  }

  if (derg.set_min_pf_under_excited.is_initialized()) {
    path = "DERSettings.setMinPFUnderExcited.displacement";
    pt->put(path, derg.set_min_pf_under_excited.get().displacement);
    path = "DERSettings.setMinPFUnderExcited.multiplier";
    pt->put(path, derg.set_min_pf_under_excited.get().multiplier);
  }

  if (derg.set_min_v.is_initialized()) {
    path = "DERSettings.setMinV.value";
    pt->put(path, derg.set_min_v.get().value);
    path = "DERSettings.setMinV.multiplier";
    pt->put(path, derg.set_min_v.get().multiplier);
  }

  if (derg.set_normal_category.is_initialized()) {
    path = "DERSettings.setNormalCategory";
    pt->put(path, util::ToUnderlyingType(derg.set_normal_category.get()));
  }

  if (derg.set_over_excited_pf.is_initialized()) {
    path = "DERSettings.setOverExcitedPF.displacement";
    pt->put(path, derg.set_over_excited_pf.get().displacement);
    path = "DERSettings.setOverExcitedPF.multiplier";
    pt->put(path, derg.set_over_excited_pf.get().multiplier);
  }

  if (derg.set_over_excited_w.is_initialized()) {
    path = "DERSettings.setOverExcitedW.value";
    pt->put(path, derg.set_over_excited_w.get().value);
    path = "DERSettings.setOverExcitedW.multiplier";
    pt->put(path, derg.set_over_excited_w.get().multiplier);
  }

  if (derg.set_reactive_susceptance.is_initialized()) {
    path = "DERSettings.setReactiveSusceptance.value";
    pt->put(path, derg.set_reactive_susceptance.get().value);
    path = "DERSettings.setReactiveSusceptance.multiplier";
    pt->put(path, derg.set_reactive_susceptance.get().multiplier);
  }

  if (derg.set_under_excited_w.is_initialized()) {
    path = "DERSettings.setUnderExcitedW.value";
    pt->put(path, derg.set_under_excited_w.get().value);
    path = "DERSettings.setUnderExcitedW.multiplier";
    pt->put(path, derg.set_under_excited_w.get().multiplier);
  }

  if (derg.set_v_nom.is_initialized()) {
    path = "DERSettings.setVNom.value";
    pt->put(path, derg.set_v_nom.get().value);
    path = "DERSettings.setVNom.multiplier";
    pt->put(path, derg.set_v_nom.get().multiplier);
  }
};

std::string Serialize(const sep::DERSettings &derg) {
  boost::property_tree::ptree pt;
  TreeMap(derg, &pt);

  xml::util::SetSchema(&pt);
  return xml::util::Stringify(&pt);
}

void Parse(const std::string &xml_str, sep::DERSettings *derg) {
  boost::property_tree::ptree pt = xml::util::Treeify(xml_str);
  ObjectMap(pt, derg);
}
} // namespace xml
