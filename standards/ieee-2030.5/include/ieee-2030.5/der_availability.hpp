#ifndef __DER_AVAILABILITY_H__
#define __DER_AVAILABILITY_H__
#include <cstdint>
#include "subscribable_resource.hpp"
#include "time_type.hpp"
#include "per_cent.hpp"
#include "reactive_power.hpp"
#include "active_power.hpp"

namespace sep
{
    // Indicates current reserve generation status
    struct DERAvailability : SubscribableResource
    {
        uint32_t availability_duration;
        uint32_t max_charge_duration;
        TimeType reading_time;
        PerCent reserve_charge_percent;
        PerCent reserve_percent;
        ReactivePower stat_var_avail;
        ActivePower stat_w_avail;

    };
    
} // namespace sep

#endif // __DER_AVAILABILITY_H__