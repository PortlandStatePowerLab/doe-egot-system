#ifndef __LOCAL_CONTROL_MODE_STATUS_TYPE_H__
#define __LOCAL_CONTROL_MODE_STATUS_TYPE_H__
#include <cstdint>
#include "time_type.hpp"

namespace sep
{
    struct LocalControlModeStatusType
    {
        enum class ControlStatus : uint32_t
        {
            kLocal,
            kRemote
        };

        TimeType date_time;
        ControlStatus value;
    };
    
} // namespace sep

#endif // __LOCAL_CONTROL_MODE_STATUS_TYPE_H__