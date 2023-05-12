#ifndef __TIME_H__
#define __TIME_H__
#include "simple_types.hpp"
#include "time_offset_type.hpp"

namespace sep
{
    struct TimeLink : Link {};
    
    // Contains the representation of time, constantly updated.
    struct Time : Resource
    {
        TimeType current_time;
        TimeType dst_end_time;
        TimeOffsetType dst_offset;
        TimeType dst_start_time;
        TimeType local_time;
        UInt8 quality;
        TimeOffsetType tz_offset;
        UInt32 poll_rate = 900;
    };
    
} // namespace sep

#endif // __TIME_H__