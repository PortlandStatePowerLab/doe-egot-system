#ifndef __LOCAL_CONTROL_MODE_STATUS_TYPE_H__
#define __LOCAL_CONTROL_MODE_STATUS_TYPE_H__
#include "simple_types.hpp"

namespace sep
{
    struct LocalControlModeStatusType
    {
        enum class ControlStatus : UInt8
        {
            kLocal,
            kRemote
        };

        TimeType date_time;
        ControlStatus value;
    };
    
} // namespace sep

#endif // __LOCAL_CONTROL_MODE_STATUS_TYPE_H__