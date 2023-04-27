#ifndef __REACTIVE_POWER_H__
#define __REACTIVE_POWER_H__
#include "simple_types.hpp"

namespace sep
{
    // The reactive power Q (in var) is the product of root mean square (RMS)
    // voltage, RMS current, and sin(theta) where theta is the phase angle of
    // current relative to voltage.
    struct ReactivePower
    {
        PowerOfTenMultiplierType multiplier;
        UInt16 value;
    };
};     // namespace sep
#endif // __REACTIVE_POWER_H__