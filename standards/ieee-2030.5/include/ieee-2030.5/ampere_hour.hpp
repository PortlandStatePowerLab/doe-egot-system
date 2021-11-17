#ifndef __AMPERE_HOUR_H__
#define __AMPERE_HOUR_H__
#include <cstdint>
#include "power_of_ten_multiplier_type.hpp"

namespace sep
{
    // Available electric charge
    struct AmpereHour
    {
        PowerOfTenMultiplierType multiplier;
        uint16_t value;
    };
    
} // namespace sep

#endif // __AMPERE_HOUR_H__