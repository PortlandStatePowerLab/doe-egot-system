#ifndef __INVERTER_STATUS_TYPE_H__
#define __INVERTER_STATUS_TYPE_H__
#include <cstdint>
#include "time_type.hpp"

namespace sep
{
    struct InverterStatusType
    {
        enum class Status : uint8_t
        {
            kNA,
            kOff,
            kSleeping,
            kStarting,
            kTrackingMPPT,
            kForcedPowerReduction,
            kShuttingDown,
            kFault,
            kStandby,
            kTestMode,
            kManufacturerStatus
        };

        TimeType date_time;
        Status value;
    };
    
} // namespace sep

#endif // __INVERTER_STATUS_TYPE_H__