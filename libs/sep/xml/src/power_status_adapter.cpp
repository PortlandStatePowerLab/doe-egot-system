#include "sep/models/simple_types.hpp"
#include <sep/xml/power_status_adapter.hpp>
#include <sep/xml/utilities.hpp>

namespace xml
{
    void ObjectMap (const boost::property_tree::ptree &pt, sep::PowerStatus *ps)
    {
        std::string path = "PowerStatus.<xmlattr>.href";
        ps->href = pt.get<std::string>(path, "");
        path = "PowerStatus.<xmlattr>.pollRate";
        ps->poll_rate = pt.get<sep::UInt32>(path, 0);
        path = "PowerStatus.batteryStatus";
        ps->battery_status = static_cast<sep::BatteryStatus>(pt.get<sep::UInt8>(path, 0));
        path = "PowerStatus.changedTime";
        ps->changed_time = pt.get<sep::TimeType>(path, 0);
        path = "PowerStatus.currentPowerSource";
        ps->current_power_source = static_cast<sep::PowerSourceType>(pt.get<sep::UInt8>(path, 0));
        path = "PowerStatus.estimatedChargeRemaining";
        if(auto charge_remaining = pt.get_optional<sep::PerCent>(path)){
            ps->estimated_charge_remaining.value() = charge_remaining.value();
        }
        path = "PowerStatus.estimatedTimeRemaining";
        if(auto time_remaining = pt.get_optional<sep::TimeType>(path)){
            ps->estimated_time_remaining.value() = time_remaining.value();
        }
        path = "PowerStatus.PEVInfo.chargingPowerNow.multiplier";
        if(auto multiplier = pt.get_optional<sep::PowerOfTenMultiplierType>(path)){
            ps->pev_info.value().charging_power_now.multiplier = multiplier.value();
        }
        path = "PowerStatus.PEVInfo.chargingPowerNow.value";
        if(auto value = pt.get_optional<sep::Int16>(path)){
            ps->pev_info.value().charging_power_now.value = value.value();
        }
        path = "PowerStatus.PEVInfo.energyRequestNow.multiplier";
        if(auto multiplier = pt.get_optional<sep::PowerOfTenMultiplierType>(path)){
            ps->pev_info.value().energy_request_now.multiplier = multiplier.value();
        }
        path = "PowerStatus.PEVInfo.energyRequestNow.value";
        if(auto value = pt.get_optional<sep::UInt48>(path)){
            ps->pev_info.value().energy_request_now.value = value.value();
        }
        path = "PowerStatus.PEVInfo.maxForwardPower.multiplier";
        if(auto multiplier = pt.get_optional<sep::PowerOfTenMultiplierType>(path)){
            ps->pev_info.value().max_forward_power.multiplier = multiplier.value();
        }
        path = "PowerStatus.PEVInfo.maxForwardPower.multiplier";
        if(auto value = pt.get_optional<sep::Int16>(path)){
            ps->pev_info.value().max_forward_power.value = value.value();
        }
        path = "PowerStatus.PEVInfo.minimumChargingDuration";
        if(auto charge_duration = pt.get_optional<sep::UInt32>(path)){
            ps->pev_info.value().minimum_charging_duration = charge_duration.value();
        }
        path = "PowerStatus.PEVInfo.targetStateOfCharge";
        if(auto target_soc = pt.get_optional<sep::PerCent>(path)){
            ps->pev_info.value().target_state_of_charge = target_soc.value();
        }
        path = "PowerStatus.PEVInfo.timeChargeIsNeeded";
        if(auto time_needed = pt.get_optional<sep::TimeType>(path)){
            ps->pev_info.value().time_charge_is_needed = time_needed.value();
        }
        path = "PowerStatus.PEVInfo.timeChargingStatusPEV";
        if(auto charging_status = pt.get_optional<sep::TimeType>(path)){
            ps->pev_info.value().time_charging_status_pev = charging_status.value();
        }
        path = "PowerStatus.sessionTimeOnBattery";
        if(auto session_time_on = pt.get_optional<sep::UInt32>(path)){
            ps->session_time_on_battery.value() = session_time_on .value();
        }
        path = "PowerStatus.totalTimeOnBattery";
        if(auto total_time_on = pt.get_optional<sep::UInt32>(path)){
            ps->total_time_on_battery.value() = total_time_on.value();
        }
    }

    void TreeMap (const sep::PowerStatus &ps, boost::property_tree::ptree *pt)
    {
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
        if(ps.estimated_charge_remaining.has_value()){
            path = "PowerStatus.estimatedChargeRemaining";
            pt->put(path, ps.estimated_charge_remaining.value());
        }
        if(ps.estimated_time_remaining.has_value()){
            path = "PowerStatus.estimatedTimeRemaining";
            pt->put(path, ps.estimated_time_remaining.value());;
        }
        if(ps.pev_info.has_value()){
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
        if(ps.session_time_on_battery.has_value()){
            path = "PowerStatus.sessionTimeOnBattery";
            pt->put(path, ps.session_time_on_battery.value());
        }
        if(ps.total_time_on_battery.has_value()){
            path = "PowerStatus.totalTimeOnBattery";
            pt->put(path, ps.total_time_on_battery.value());
        }
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
