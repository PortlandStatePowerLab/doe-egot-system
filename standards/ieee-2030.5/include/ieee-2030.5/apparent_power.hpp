#ifndef __APPARENT_POWER_H__
#define __APPARENT_POWER_H__
#include <cstdint>
#include "power_of_ten_multiplier_type.hpp"

namespace sep
{
    // The apparent power S (in VA) is 
    // the product of root mean square (RMS) voltage and RMS current.
    struct ApparentPower
    {
        PowerOfTenMultiplierType multiplier;
        uint16_t value;
    };
    
} // namespace sep

#endif // __APPARENT_POWER_H__