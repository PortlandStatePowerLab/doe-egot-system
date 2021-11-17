#ifndef __CURRENT_RMS_H__
#define __CURRENT_RMS_H__
#include <cstdint>
#include "power_of_ten_multiplier_type.hpp"

namespace sep
{
    // Average flow of charge through a conductor.
    struct CurrentRMS
    {
        PowerOfTenMultiplierType multiplier;
        uint16_t value;
    };
    
} // namespace sep

#endif // __CURRENT_RMS_H__