#ifndef __POWER_SOURCE_TYPE_H__
#define __POWER_SOURCE_TYPE_H__

#include <cstdint>

namespace sep
{
    enum class PowerSourceType : uint8_t
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