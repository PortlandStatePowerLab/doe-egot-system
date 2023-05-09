#ifndef __OPERATIONAL_MODE_STATUS_TYPE_H__
#define __OPERATIONAL_MODE_STATUS_TYPE_H__
#include "simple_types.hpp"

namespace sep
{
    struct OperationalModeStatusType
    {
        enum class Status : UInt8
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