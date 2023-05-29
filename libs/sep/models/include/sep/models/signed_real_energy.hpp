#ifndef __SIGNED_REAL_ENERGY_H__
#define __SIGNED_REAL_ENERGY_H__
#include "simple_types.hpp"

namespace sep
{
    // Real electrical energy, signed
    struct SignedRealEnergy
    {
        PowerOfTenMultiplierType multiplier;
        Int48 value; // Watt-hours
    };
};     // namespace sep
#endif // __SIGNED_REAL_ENERGY_H__