#ifndef __CONNECT_STATUS_TYPE_H__
#define __CONNECT_STATUS_TYPE_H__
#include "simple_types.hpp"

namespace sep
{
    struct ConnectStatusType
    {
        enum class Status : UInt8
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