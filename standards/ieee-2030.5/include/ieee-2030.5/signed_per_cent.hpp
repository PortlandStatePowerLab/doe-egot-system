#ifndef __SIGNED_PER_CENT_H__
#define __SIGNED_PER_CENT_H__
#include <cstdint>

namespace sep
{
    // Used for signed percentages, specified in hundredths of a percent,
    // -10000 to 10000. (10000 = 100%)
    using SignedPerCent = uint16_t;
};     // namespace sep
#endif // __SIGNED_PER_CENT_H__