#ifndef __RANDOMIZE_EVENT_H__
#define __RANDOMIZE_EVENT_H__
#include "event.hpp"
#include "one_hour_range_type.hpp"

namespace sep {
///
/// An Event that can indicate time ranges over which the start time
/// and duration SHALL be randomized.
///
struct RandomizableEvent {
  Event event;
  OneHourRangeType randomize_duration;
  OneHourRangeType randomize_start;
};
};     // namespace sep
#endif // __RANDOMIZE_EVENT_H__
