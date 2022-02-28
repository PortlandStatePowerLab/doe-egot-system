#ifndef __TEMPERATURE_H__
#define __TEMPERATURE_H__

#include "power_of_ten_multiplier_type.hpp"

namespace sep
{
    // Specification of a temperature.
    struct Temperature
    {
        enum class Subject : uint8_t
        {
            Enclosure,
            Transformer,
            HeatSink
        };

        PowerOfTenMultiplierType multiplier;
        Subject subject;
        int16_t value;
    };
    
} // namespace sep

#endif // __TEMPERATURE_H__