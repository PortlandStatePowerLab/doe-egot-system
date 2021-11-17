#ifndef __VOLTAGE_RMS_H__
#define __VOLTAGE_RMS_H__
#include <cstdint>
#include "power_of_ten_multiplier_type.hpp"

namespace sep
{
    // Average electric potential difference between two points.
    struct VoltageRMS
    {
        PowerOfTenMultiplierType multiplier;
        uint16_t value;
    };
    
} // namespace sep

#endif // __VOLTAGE_RMS_H__