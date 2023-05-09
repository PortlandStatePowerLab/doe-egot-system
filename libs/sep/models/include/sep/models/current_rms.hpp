#ifndef __CURRENT_RMS_H__
#define __CURRENT_RMS_H__
#include "simple_types.hpp"

namespace sep
{
    // Average flow of charge through a conductor.
    struct CurrentRMS
    {
        PowerOfTenMultiplierType multiplier;
        UInt16 value;
    };
    
} // namespace sep

#endif // __CURRENT_RMS_H__