#ifndef __INVERTER_STATUS_TYPE_H__
#define __INVERTER_STATUS_TYPE_H__
#include "simple_types.hpp"

namespace sep
{
    struct InverterStatusType
    {
        enum class Status : UInt8
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