#ifndef __RANDOMIZE_EVENT_H__
#define __RANDOMIZE_EVENT_H__
#include <cstdint>
#include "event.hpp"
#include "one_hour_range_type.hpp"

namespace sep
{
    // An Event that can indicate time ranges over which the start time
    // and duration SHALL be randomized.
    struct RandomizableEvent
    {
        sep::Event event;
        sep::OneHourRangeType randomize_duration;
        sep::OneHourRangeType randomize_start;
    };
};     // namespace sep
#endif // __RANDOMIZE_EVENT_H__