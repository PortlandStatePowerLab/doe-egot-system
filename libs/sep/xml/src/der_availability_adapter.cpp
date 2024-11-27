#include "sep/models/der_availability.hpp"
#include <boost/optional.hpp>
#include <sep/models/simple_types.hpp>
#include <sep/xml/der_availability_adapter.hpp>
#include <sep/xml/utilities.hpp>

namespace xml {
void ObjectMap(const boost::property_tree::ptree &pt,
               sep::DERAvailability *dera) {
  std::string path = "DERAvailability.<xmlattr>.href";
  dera->href = pt.get<std::string>(path);

  path = "DERAvailability.<xmlattr>.subscribable";
  dera->subscribable =
      static_cast<sep::SubscribableType>(pt.get<sep::UInt8>(path, 0));

  path = "DERAvailability.readingTime";
  dera->reading_time = pt.get<sep::TimeType>(path, 0);

  path = "DERAvailability.availabilityDuration";
  if (auto opt = pt.get_optional<sep::UInt32>(path)) {
    dera->availability_duration.emplace(opt.value());
  }

  path = "DERAvailability.maxChargeDuration";
  if (auto opt = pt.get_optional<sep::UInt32>(path)) {
    dera->max_charge_duration.emplace(opt.value());
  }

  path = "DERAvailability.reserveChargePercent";
  if (auto opt = pt.get_optional<sep::PerCent>(path)) {
    dera->reserve_charge_percent.emplace(opt.value());
  }

  path = "DERAvailability.reservePercent";
  if (auto opt = pt.get_optional<sep::PerCent>(path)) {
    dera->reserve_percent.emplace(opt.value());
  }

  path = "DERAvailability.statWAvail";
  if (auto child = pt.get_child_optional(path)) {
    auto multi =
        child.value().get<sep::PowerOfTenMultiplierType>("multiplier", 0);
    auto val = child.value().get<sep::Int16>("value", 0);
    sep::ActivePower obj;
    obj.multiplier = multi;
    obj.value = val;
    dera->stat_w_avail = obj;
  }

  path = "DERAvailability.statVarAvail";
  if (auto child = pt.get_child_optional(path)) {
    auto multi =
        child.value().get<sep::PowerOfTenMultiplierType>("multiplier", 0);
    auto val = child.value().get<sep::Int16>("value", 0);
    sep::ReactivePower obj;
    obj.multiplier = multi;
    obj.value = val;
    dera->stat_var_avail = obj;
  }
};

void TreeMap(const sep::DERAvailability &dera,
             boost::property_tree::ptree *pt) {
  std::string path = "DERAvailability.<xmlattr>.href";
  pt->put(path, dera.href);

  path = "DERAvailability.<xmlattr>.subscribable";
  pt->put(path, util::ToUnderlyingType(dera.subscribable));

  path = "DERAvailability.readingTime";
  pt->put(path, dera.reading_time);

  if (dera.availability_duration.is_initialized()) {
    path = "DERAvailability.availabilityDuration";
    pt->put(path, dera.availability_duration.get());
  }

  if (dera.max_charge_duration.is_initialized()) {
    path = "DERAvailability.maxChargeDuration";
    pt->put(path, dera.max_charge_duration.get());
  }

  if (dera.reserve_charge_percent.is_initialized()) {
    path = "DERAvailability.reserveChargePercent";
    pt->put(path, dera.reserve_charge_percent.get());
  }

  if (dera.reserve_percent.is_initialized()) {
    path = "DERAvailability.reservePercent";
    pt->put(path, dera.reserve_percent.get());
  }

  if (dera.stat_var_avail.is_initialized()) {
    path = "DERAvailability.statVarAvail.multiplier";
    pt->put(path, dera.stat_var_avail.get().multiplier);
    path = "DERAvailability.statVarAvail.value";
    pt->put(path, dera.stat_var_avail.get().value);
  }

  if (dera.stat_w_avail.is_initialized()) {
    path = "DERAvailability.statWAvail.multiplier";
    pt->put(path, dera.stat_w_avail.get().multiplier);
    path = "DERAvailability.statWAvail.value";
    pt->put(path, dera.stat_w_avail.get().value);
  }
};

std::string Serialize(const sep::DERAvailability &dera) {
  boost::property_tree::ptree pt;
  TreeMap(dera, &pt);

  xml::util::SetSchema(&pt);
  return xml::util::Stringify(&pt);
}

void Parse(const std::string &xml_str, sep::DERAvailability *dera) {
  boost::property_tree::ptree pt = xml::util::Treeify(xml_str);
  ObjectMap(pt, dera);
}
} // namespace xml
