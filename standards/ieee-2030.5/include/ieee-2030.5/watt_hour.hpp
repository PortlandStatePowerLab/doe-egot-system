#ifndef __WATT_HOUR_H__
#define __WATT_HOUR_H__
#include <cstdint>
#include "power_of_ten_multiplier_type.hpp"

namespace sep
{
    // Active (real) energy
    struct WattHour
    {
        PowerOfTenMultiplierType multiplier;
        uint16_t value;
    };
    
} // namespace sep

#endif // __WATT_HOUR_H__