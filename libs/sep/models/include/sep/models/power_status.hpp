#ifndef __POWER_STATUS_H__
#define __POWER_STATUS_H__

#include "simple_types.hpp"
#include "power_source_type.hpp"
#include "per_cent.hpp"
#include "pev_info.hpp"

namespace sep
{
    enum class BatteryStatus : UInt8
    {
        kUnknown,
        kNormal,
        kLow,
        kDepleted,
        kNA
    };

    struct PowerStatusListLink : ListLink {};
    struct PowerStatusLink : Link {};

    // Contains the status of the device's power sources
    struct PowerStatus : Resource
    {
        BatteryStatus battery_status;
        TimeType changed_time;
        PowerSourceType current_power_source;
        PerCent estimated_charge_remaining;
        UInt32 estimated_time_remaining;
        PEVInfo pev_info;
        UInt32 session_time_on_battery;
        UInt32 total_time_on_battery;
        UInt32 poll_rate;
    };
    
} // namespace sep

#endif // __POWER_STATUS_H__