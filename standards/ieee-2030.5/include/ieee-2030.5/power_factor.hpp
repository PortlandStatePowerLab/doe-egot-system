#ifndef __POWER_FACTOR_H__
#define __POWER_FACTOR_H__
#include <cstdint>
#include "power_of_ten_multiplier_type.hpp"

namespace sep
{
    // Specifies a setpoint for Displacement Power Factor, the ratio between 
    // apparent and active powers at the fundamental frequency (e.g. 60 Hz).
    struct PowerFactor
    {
        uint16_t displacement;
        PowerOfTenMultiplierType multiplier;
    };
    
} // namespace sep

#endif // __POWER_FACTOR_H__