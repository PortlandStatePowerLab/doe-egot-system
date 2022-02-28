#ifndef __DEVICE_STATUS_H__
#define __DEVICE_STATUS_H__

#include "resource.hpp"
#include "time_type.hpp"
#include "link.hpp"
#include "temperature.hpp"

namespace sep
{
    // Status of device
    struct DeviceStatus : Resource
    {
        enum class OpState : uint8_t
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
        uint16_t on_count;
        OpState op_state;
        uint32_t op_time;
        Temperature temperature;
        Link time_link;
        uint32_t poll_rate;
    };

} // namespace sep

#endif // __DEVICE_STATUS_H__