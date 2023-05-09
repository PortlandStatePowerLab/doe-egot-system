#ifndef __DEVICE_STATUS_H__
#define __DEVICE_STATUS_H__

#include "simple_types.hpp"
#include "time.hpp"
#include "temperature.hpp"

namespace sep
{
    struct DeviceStatusListLink : ListLink {};
    struct DeviceStatusLink : Link {};
    
    // Status of device
    struct DeviceStatus : Resource
    {
        enum class OpState : UInt8
        {
            kUnknown,
            kNotOperating,
            kOperating,
            kStartingUp,
            kShuttingDown,
            kAtDisconnectLevel,
            kRampingKiloWatt,
            kRampingKiloVar
        };

        TimeType changed_time;
        UInt16 on_count;
        OpState op_state;
        UInt32 op_time;
        Temperature temperature;
        TimeLink time_link;
        UInt32 poll_rate;
    };

} // namespace sep

#endif // __DEVICE_STATUS_H__