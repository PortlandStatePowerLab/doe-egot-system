#ifndef __ACTIVE_POWER_H__
#define __ACTIVE_POWER_H__
#include <cstdint>
#include "power_of_ten_multiplier_type.hpp"

namespace sep
{
    // The active (real) power P (in W) is the product of root-mean-square (RMS)
    // voltage, RMS current, and cos(theta) where theta is the phase angle of
    // current relative to voltage.  It is the primary measure of the rate of
    // flow of energy.
    struct ActivePower
    {
        sep::PowerOfTenMultiplierType multiplier;
        int16_t value; // watts
    };
}; // namespace sep

#endif // __ACTIVE_POWER_H__