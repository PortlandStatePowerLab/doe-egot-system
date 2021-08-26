#ifndef __TIME_OFFSET_TYPE_H__
#define __TIME_OFFSET_TYPE_H__
#include <cstdint>

namespace sep
{
    // A signed time offset, typically applied to a Time value, expressed in seconds.
    using TimeOffsetType = int32_t;
} // namespace sep

#endif // __TIME_OFFSET_TYPE_H__