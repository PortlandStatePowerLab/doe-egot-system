#ifndef __OPERATIONAL_MODE_STATUS_TYPE_H__
#define __OPERATIONAL_MODE_STATUS_TYPE_H__
#include <cstdint>
#include "time_type.hpp"

namespace sep
{
    struct OperationalModeStatusType
    {
        enum class Status : uint8_t
        {
            kNA,
            kOff,
            kOperationalMode,
            kTestMode
        };

        TimeType date_time;
        Status value;
    };
    
} // namespace sep

#endif // __OPERATIONAL_MODE_STATUS_TYPE_H__