#ifndef __PEV_INFO_H__
#define __PEV_INFO_H__

#include "active_power.hpp"
#include "real_energy.hpp"
#include "per_cent.hpp"

namespace sep
{
    struct PEVInfo
    {
        ActivePower charging_power_now;
        RealEnergy energy_request_now;
        ActivePower max_forward_power;
        uint32_t minimum_charging_duration;
        PerCent target_state_of_charge;
        TimeType time_charge_is_needed;
        TimeType time_charging_status_pev;
    };
    
} // namespace sep

#endif // __PEV_INFO_H__