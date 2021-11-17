#ifndef __KIND_TYPE_H__
#define __KIND_TYPE_H__
#include <cstdint>

namespace sep
{
    enum class KindType : uint8_t
    {
        kNA,
        kCurrency = 3,
        kDemand = 8,
        kEnergy = 12,
        kPower = 37
    };

} // namespace sep

#endif // __KIND_TYPE_H__