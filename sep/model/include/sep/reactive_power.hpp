#ifndef __REACTIVE_POWER_H__
#define __REACTIVE_POWER_H__
#include <cstdint>
#include "power_of_ten_multiplier_type.hpp"

namespace sep
{
    // The reactive power Q (in var) is the product of root mean square (RMS)
    // voltage, RMS current, and sin(theta) where theta is the phase angle of
    // current relative to voltage.
    struct ReactivePower
    {
        sep::PowerOfTenMultiplierType multiplier;
        int16_t value;
    };
};     // namespace sep
#endif // __REACTIVE_POWER_H__