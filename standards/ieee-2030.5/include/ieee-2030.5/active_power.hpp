#ifndef __ACTIVE_POWER_H__
#define __ACTIVE_POWER_H__
#include "simple_types.hpp"

namespace sep
{
    // The active (real) power P (in W) is the product of root-mean-square (RMS)
    // voltage, RMS current, and cos(theta) where theta is the phase angle of
    // current relative to voltage.  It is the primary measure of the rate of
    // flow of energy.
    struct ActivePower
    {
        PowerOfTenMultiplierType multiplier;
        Int16 value; // watts
    };
}; // namespace sep

#endif // __ACTIVE_POWER_H__