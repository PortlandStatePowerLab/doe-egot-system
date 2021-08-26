#ifndef __DATE_TIME_INTERVAL_H__
#define __DATE_TIME_INTERVAL_H__
#include <cstdint>
#include "time_type.hpp"

namespace sep
{
    // Interval of date and time
    struct DateTimeInterval
    {
        uint32_t duration;
        sep::TimeType start;
    };
} // namespace sep

#endif // __DATE_TIME_INTERVAL_H__