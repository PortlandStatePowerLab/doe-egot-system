#ifndef __STORAGE_MODE_STATUS_TYPE_H__
#define __STORAGE_MODE_STATUS_TYPE_H__
#include <cstdint>
#include "time_type.hpp"

namespace sep
{
    struct StorageModeStatusType
    {
        enum class Status : uint8_t
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