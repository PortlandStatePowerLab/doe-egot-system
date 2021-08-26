#ifndef __TIME_H__
#define __TIME_H__
#include <cstdint>
#include "resource.hpp"
#include "time_type.hpp"
#include "time_offset_type.hpp"

namespace sep
{
    // Contains the representation of time, constantly updated.
    struct Time : Resource
    {
        sep::TimeType current_time;
        sep::TimeType dst_end_time;
        sep::TimeOffsetType dst_offset;
        sep::TimeType dst_start_time;
        sep::TimeType local_time;
        uint8_t quality;
        sep::TimeOffsetType tz_offset;
        uint32_t poll_rate = 900;
    };
    
} // namespace sep

#endif // __TIME_H__