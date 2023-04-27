#ifndef __POWER_SOURCE_TYPE_H__
#define __POWER_SOURCE_TYPE_H__

#include "simple_types.hpp"

namespace sep
{
    enum class PowerSourceType : UInt8
    {
        kNone,
        kMains,
        kBattery,
        kLocalGeneration,
        kEmergency,
        kUnknown
    };
    
} // namespace sep

#endif // __POWER_SOURCE_TYPE_H__