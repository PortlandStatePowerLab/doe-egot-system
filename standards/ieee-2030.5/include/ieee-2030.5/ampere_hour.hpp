#ifndef __AMPERE_HOUR_H__
#define __AMPERE_HOUR_H__
#include "simple_types.hpp"

namespace sep
{
    // Available electric charge
    struct AmpereHour
    {
        PowerOfTenMultiplierType multiplier;
        UInt16 value;
    };
    
} // namespace sep

#endif // __AMPERE_HOUR_H__