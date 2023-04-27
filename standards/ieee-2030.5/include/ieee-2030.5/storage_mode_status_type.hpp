#ifndef __STORAGE_MODE_STATUS_TYPE_H__
#define __STORAGE_MODE_STATUS_TYPE_H__
#include "simple_types.hpp"

namespace sep
{
    struct StorageModeStatusType
    {
        enum class Status : UInt8
        {
            kCharging,
            kDischarging,
            kHolding
        };

        TimeType date_time;
        Status value;
    };
    
} // namespace sep

#endif // __STORAGE_MODE_STATUS_TYPE_H__