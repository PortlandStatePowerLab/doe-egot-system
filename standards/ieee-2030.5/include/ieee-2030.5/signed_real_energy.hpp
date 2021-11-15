#ifndef __SIGNED_REAL_ENERGY_H__
#define __SIGNED_REAL_ENERGY_H__
#include <cstdint>
#include "power_of_ten_multiplier_type.hpp"

namespace sep
{
    // Real electrical energy, signed
    struct SignedRealEnergy
    {
        sep::PowerOfTenMultiplierType multiplier;
        int64_t value : 48; // Watt-hours
    };
};     // namespace sep
#endif // __SIGNED_REAL_ENERGY_H__