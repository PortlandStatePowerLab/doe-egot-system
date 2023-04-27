#ifndef __REAL_ENERGY_H__
#define __REAL_ENERGY_H__

#include "simple_types.hpp"

namespace sep
{
    // Real electrical energy
    struct RealEnergy
    {
        PowerOfTenMultiplierType multiplier;
        UInt48 value;
    };
} // namespace sep

#endif // __REAL_ENERGY_H__