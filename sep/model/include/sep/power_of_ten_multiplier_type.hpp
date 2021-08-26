#ifndef __POWER_OF_TEN_MULTIPLIER_TYPE_H__
#define __POWER_OF_TEN_MULTIPLIER_TYPE_H__
#include <cstdint>

namespace sep
{
    // This is not a complete list. Any integer between -9 and 9 SHALL be
    // supported, indicating the power of ten multiplier for the units.
    using PowerOfTenMultiplierType = int8_t;
    
};     // namespace sep
#endif // __POWER_OF_TEN_MULTIPLIER_TYPE_H__