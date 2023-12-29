#include "sep/models/simple_types.hpp"
#include <sep/xml/power_status_adapter.hpp>
#include <sep/xml/utilities.hpp>

namespace xml {
void ObjectMap(const boost::property_tree::ptree &pt, sep::PowerStatus *ps) {
  std::string path = "PowerStatus.<xmlattr>.href";
  ps->href = pt.get<std::string>(path, "");
  path = "PowerStatus.<xmlattr>.pollRate";
  ps->poll_rate = pt.get<sep::UInt32>(path, 0);
  path = "PowerStatus.batteryStatus";
  ps->battery_status =
      static_cast<sep::BatteryStatus>(pt.get<sep::UInt8>(path, 0));
  path = "PowerStatus.changedTime";
  ps->changed_time = pt.get<sep::TimeType>(path, 0);
  path = "PowerStatus.currentPowerSource";
  ps->current_power_source =
      static_cast<sep::PowerSourceType>(pt.get<sep::UInt8>(path, 0));
  path = "PowerStatus.estimatedChargeRemaining";
  if (auto charge_remaining = pt.get_optional<sep::PerCent>(path)) {
    ps->estimated_charge_remaining.emplace(charge_remaining.value());
  }
  path = "PowerStatus.estimatedTimeRemaining";
  if (auto time_remaining = pt.get_optional<sep::TimeType>(path)) {
    ps->estimated_time_remaining.emplace(time_remaining.value());
  }
  path = "PowerStatus.PEVInfo";
  if (auto child = pt.get_child_optional(path)) {
    sep::PEVInfo info;
    info.charging_power_now.multiplier =
        child.value().get<sep::PowerOfTenMultiplierType>(
            "chargingPowerNow.multiplier", 0);
    info.charging_power_now.value =
        child.value().get<sep::Int16>("chargingPowerNow.value", 0);
    info.energy_request_now.multiplier =
        child.value().get<sep::PowerOfTenMultiplierType>(
            "energyRequestNow.multiplier", 0);
    info.energy_request_now.value =
        child.value().get<sep::Int16>("energyRequestNow.value", 0);
    info.max_forward_power.multiplier =
        child.value().get<sep::PowerOfTenMultiplierType>(
            "maxForwardPower.multiplier", 0);
    info.max_forward_power.value =
        child.value().get<sep::Int16>("maxForwardPower.value", 0);
    info.minimum_charging_duration =
        child.value().get<sep::UInt32>("minimumChargingDuration", 0);
    info.target_state_of_charge =
        child.value().get<sep::PerCent>("targetStateOfCharge", 0);
    info.time_charge_is_needed =
        child.value().get<sep::TimeType>("timeChargeIsNeeded", 0);
    info.time_charging_status_pev =
        child.value().get<sep::TimeType>("timeChargingStatusPEV", 0);
    ps->pev_info.emplace(info);
  }
  path = "PowerStatus.sessionTimeOnBattery";
  if (auto session_time_on = pt.get_optional<sep::UInt32>(path)) {
    ps->session_time_on_battery.emplace(session_time_on.value());
  }
  path = "PowerStatus.totalTimeOnBattery";
  if (auto total_time_on = pt.get_optional<sep::UInt32>(path)) {
    ps->total_time_on_battery.emplace(total_time_on.value());
  }
}

void TreeMap(const sep::PowerStatus &ps, boost::property_tree::ptree *pt) {
  std::string path = "PowerStatus.<xmlattr>.href";
  pt->put(path, ps.href);
  path = "PowerStatus.<xmlattr>.pollRate";
  pt->put(path, ps.poll_rate);
  path = "PowerStatus.batteryStatus";
  pt->put(path, xml::util::ToUnderlyingType(ps.battery_status));
  path = "PowerStatus.changedTime";
  pt->put(path, ps.changed_time);
  path = "PowerStatus.currentPowerSource";
  pt->put(path, xml::util::ToUnderlyingType(ps.current_power_source));
  if (ps.estimated_charge_remaining.is_initialized()) {
    path = "PowerStatus.estimatedChargeRemaining";
    pt->put(path, ps.estimated_charge_remaining.value());
  }
  if (ps.estimated_time_remaining.is_initialized()) {
    path = "PowerStatus.estimatedTimeRemaining";
    pt->put(path, ps.estimated_time_remaining.value());
    ;
  }
  if (ps.pev_info.is_initialized()) {
    path = "PowerStatus.PEVInfo.chargingPowerNow.multiplier";
    pt->put(path, ps.pev_info.value().charging_power_now.multiplier);
    path = "PowerStatus.PEVInfo.chargingPowerNow.value";
    pt->put(path, ps.pev_info.value().charging_power_now.value);
    path = "PowerStatus.PEVInfo.energyRequestNow.multiplier";
    pt->put(path, ps.pev_info.value().energy_request_now.multiplier);
    path = "PowerStatus.PEVInfo.energyRequestNow.value";
    pt->put(path, ps.pev_info.value().energy_request_now.value);
    path = "PowerStatus.PEVInfo.maxForwardPower.multiplier";
    pt->put(path, ps.pev_info.value().max_forward_power.multiplier);
    path = "PowerStatus.PEVInfo.maxForwardPower.value";
    pt->put(path, ps.pev_info.value().max_forward_power.value);
    path = "PowerStatus.PEVInfo.minimumChargingDuration";
    pt->put(path, ps.pev_info.value().minimum_charging_duration);
    path = "PowerStatus.PEVInfo.targetStateOfCharge";
    pt->put(path, ps.pev_info.value().target_state_of_charge);
    path = "PowerStatus.PEVInfo.timeChargeIsNeeded";
    pt->put(path, ps.pev_info.value().time_charge_is_needed);
    path = "PowerStatus.PEVInfo.timeChargingStatusPEV";
    pt->put(path, ps.pev_info.value().time_charging_status_pev);
  }
  if (ps.session_time_on_battery.is_initialized()) {
    path = "PowerStatus.sessionTimeOnBattery";
    pt->put(path, ps.session_time_on_battery.value());
  }
  if (ps.total_time_on_battery.is_initialized()) {
    path = "PowerStatus.totalTimeOnBattery";
    pt->put(path, ps.total_time_on_battery.value());
  }
}

std::string Serialize(const sep::PowerStatus &ps) {
  boost::property_tree::ptree pt;
  TreeMap(ps, &pt);

  xml::util::SetSchema(&pt);
  return xml::util::Stringify(&pt);
}

void Parse(const std::string &xml_str, sep::PowerStatus *ps) {
  boost::property_tree::ptree pt = xml::util::Treeify(xml_str);
  ObjectMap(pt, ps);
}
} // namespace xml
