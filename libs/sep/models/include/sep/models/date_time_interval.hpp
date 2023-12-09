#ifndef __DATE_TIME_INTERVAL_H__
#define __DATE_TIME_INTERVAL_H__
#include "simple_types.hpp"

namespace sep {
///
/// Interval of date and time
///
struct DateTimeInterval {
  Int32 duration;
  TimeType start;
};
} // namespace sep

#endif // __DATE_TIME_INTERVAL_H__
