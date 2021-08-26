#ifndef __POWER_FACTOR_WITH_EXCITATION_H__
#define __POWER_FACTOR_WITH_EXCITATION_H__
#include "power_of_ten_multiplier_type.hpp"
#include <cstdint>

namespace sep
{
    // Specifies a setpoint for Displacement Power Factor, the ratio between
    // apparent and active powers at the fundamental frequency (e.g. 60 Hz) and
    // includes an excitation flag.
    struct PowerFactorWithExcitation
    {
        uint16_t displacement;
        bool excitation;
        sep::PowerOfTenMultiplierType multiplier;
    };
};     // namespace sep
#endif // __POWER_FACTOR_WITH_EXCITATION_H__