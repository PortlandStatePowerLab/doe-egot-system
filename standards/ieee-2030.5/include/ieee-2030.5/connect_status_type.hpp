#ifndef __CONNECT_STATUS_TYPE_H__
#define __CONNECT_STATUS_TYPE_H__
#include <cstdint>
#include "time_type.hpp"

namespace sep
{
    struct ConnectStatusType
    {
        enum class Status : uint8_t
        {
            kConnected,
            kAvailable,
            kOperating,
            kTest,
            kFaultError
        };

        TimeType date_time;
        Status value;
    };
    
} // namespace sep

#endif // __CONNECT_STATUS_TYPE_H__