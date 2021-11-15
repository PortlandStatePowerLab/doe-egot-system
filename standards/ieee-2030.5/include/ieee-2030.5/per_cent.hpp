#ifndef __PER_CENT_H__
#define __PER_CENT_H__
#include <cstdint>

namespace sep
{
    // Used for percentages, specified in hundredths of a percent, 0 - 10000.
    // (10000 = 100%)
    using PerCent = uint16_t;
};     // namespace sep
#endif // __PER_CENT_H__