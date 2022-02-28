#ifndef __POWER_STATUS_H__
#define __POWER_STATUS_H__

#include <cstdint>
#include "resource.hpp"
#include "time_type.hpp"
#include "power_source_type.hpp"
#include "per_cent.hpp"
#include "pev_info.hpp"

namespace sep
{
    enum class BatteryStatus : uint8_t
    {
        kUnknown,
        kNormal,
        kLow,
        kDepleted,
        kNA
    };

    // Contains the status of the device's power sources
    struct PowerStatus : Resource
    {
        BatteryStatus battery_status;
        TimeType changed_time;
        PowerSourceType current_power_source;
        PerCent estimated_charge_remaining;
        uint32_t estimated_time_remaining;
        PEVInfo pev_info;
        uint32_t session_time_on_battery;
        uint32_t total_time_on_battery;
        uint32_t poll_rate;
    };
    
} // namespace sep

#endif // __POWER_STATUS_H__