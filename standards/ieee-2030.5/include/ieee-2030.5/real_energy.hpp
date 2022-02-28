#ifndef __REAL_ENERGY_H__
#define __REAL_ENERGY_H__

#include <cstdint>
#include "power_of_ten_multiplier_type.hpp"

namespace sep
{
    // Real electrical energy
    struct RealEnergy
    {
        PowerOfTenMultiplierType multiplier;
        uint64_t value;
    };
} // namespace sep

#endif // __REAL_ENERGY_H__