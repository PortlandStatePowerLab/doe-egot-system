#include "include/xml/power_status_adapter.hpp"
#include "include/xml/utilities.hpp"

namespace xml
{
    void ObjectMap (const boost::property_tree::ptree &pt, sep::PowerStatus *ps)
    {
        ps->battery_status = static_cast<sep::BatteryStatus>(pt.get<uint8_t>("PowerStatus.batteryStatus", 0));
        ps->changed_time = pt.get<sep::TimeType>("PowerStatus.changedTime", 0);
        ps->current_power_source = static_cast<sep::PowerSourceType>(pt.get<uint8_t>("PowerStatus.currentPowerSource", 0));
        ps->estimated_charge_remaining = pt.get<sep::PerCent>("PowerStatus.estimatedChargeRemaining", 0);
        ps->estimated_time_remaining = pt.get<sep::TimeType>("PowerStatus.estimatedTimeRemaining", 0);
        ps->href = pt.get<std::string>("PowerStatus.<xmlattr>.href", "");
        ps->poll_rate = pt.get<uint32_t>("PowerStatus.<xmlattr>.pollRate", 0);
        ps->pev_info.charging_power_now.multiplier = pt.get<sep::PowerOfTenMultiplierType>("PowerStatus.PEVInfo.chargingPowerNow.multiplier", 0);
        ps->pev_info.charging_power_now.value = pt.get<uint16_t>("PowerStatus.PEVInfo.chargingPowerNow.value", 0);
        ps->pev_info.energy_request_now.multiplier = pt.get<sep::PowerOfTenMultiplierType>("PowerStatus.PEVInfo.energyRequestNow.multiplier", 0);
        ps->pev_info.energy_request_now.value = pt.get<uint64_t>("PowerStatus.PEVInfo.energyRequestNow.value", 0);
        ps->pev_info.max_forward_power.multiplier = pt.get<sep::PowerOfTenMultiplierType>("PowerStatus.PEVInfo.maxForwardPower.multiplier", 0);
        ps->pev_info.max_forward_power.value = pt.get<uint16_t>("PowerStatus.PEVInfo.maxForwardPower.multiplier", 0);
        ps->pev_info.minimum_charging_duration = pt.get<uint32_t>("PowerStatus.PEVInfo.minimumChargingDuration", 0);
        ps->pev_info.target_state_of_charge = pt.get<sep::PerCent>("PowerStatus.PEVInfo.targetStateOfCharge", 0);
        ps->pev_info.time_charge_is_needed = pt.get<sep::TimeType>("PowerStatus.PEVInfo.timeChargeIsNeeded", 0);
        ps->pev_info.time_charging_status_pev = pt.get<sep::TimeType>("PowerStatus.PEVInfo.timeChargingStatusPEV", 0);
        ps->session_time_on_battery = pt.get<uint32_t>("PowerStatus.sessionTimeOnBattery", 0);
        ps->total_time_on_battery = pt.get<uint32_t>("PowerStatus.totalTimeOnBattery", 0);
    }

    void TreeMap (const sep::PowerStatus &ps, boost::property_tree::ptree *pt)
    {
        pt->put("PowerStatus.batteryStatus", xml::util::ToUnderlyingType(ps.battery_status));
        pt->put("PowerStatus.changedTime", ps.changed_time);
        pt->put("PowerStatus.currentPowerSource", xml::util::ToUnderlyingType(ps.current_power_source));
        pt->put("PowerStatus.estimatedChargeRemaining", ps.estimated_charge_remaining);
        pt->put("PowerStatus.estimatedTimeRemaining", ps.estimated_time_remaining);
        pt->put("PowerStatus.<xmlattr>.href", ps.href);
        pt->put("PowerStatus.<xmlattr>.pollRate", ps.poll_rate);
        pt->put("PowerStatus.PEVInfo.chargingPowerNow.multiplier", ps.pev_info.charging_power_now.multiplier);
        pt->put("PowerStatus.PEVInfo.chargingPowerNow.value", ps.pev_info.charging_power_now.value);
        pt->put("PowerStatus.PEVInfo.energyRequestNow.multiplier", ps.pev_info.energy_request_now.multiplier);
        pt->put("PowerStatus.PEVInfo.energyRequestNow.value", ps.pev_info.energy_request_now.value);
        pt->put("PowerStatus.PEVInfo.maxForwardPower.multiplier", ps.pev_info.max_forward_power.multiplier);
        pt->put("PowerStatus.PEVInfo.maxForwardPower.value", ps.pev_info.max_forward_power.value);
        pt->put("PowerStatus.PEVInfo.minimumChargingDuration", ps.pev_info.minimum_charging_duration);
        pt->put("PowerStatus.PEVInfo.targetStateOfCharge", ps.pev_info.target_state_of_charge);
        pt->put("PowerStatus.PEVInfo.timeChargeIsNeeded", ps.pev_info.time_charge_is_needed);
        pt->put("PowerStatus.PEVInfo.timeChargingStatusPEV", ps.pev_info.time_charging_status_pev);
        pt->put("PowerStatus.sessionTimeOnBattery", ps.session_time_on_battery);
        pt->put("PowerStatus.totalTimeOnBattery", ps.total_time_on_battery);
    }

    std::string Serialize(const sep::PowerStatus &ps)
    {
        boost::property_tree::ptree pt;
        TreeMap(ps, &pt);

        xml::util::SetSchema(&pt);
        return xml::util::Stringify(&pt);
    }

    void Parse(const std::string &xml_str, sep::PowerStatus *ps)
    {
        boost::property_tree::ptree pt = xml::util::Treeify(xml_str);
        ObjectMap(pt, ps);
    }
} // namespace xml
