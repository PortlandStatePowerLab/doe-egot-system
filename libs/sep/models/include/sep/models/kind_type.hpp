#ifndef __KIND_TYPE_H__
#define __KIND_TYPE_H__
#include "simple_types.hpp"

namespace sep
{
    enum class KindType : UInt8
    {
        kNA,
        kCurrency = 3,
        kDemand = 8,
        kEnergy = 12,
        kPower = 37
    };

} // namespace sep

#endif // __KIND_TYPE_H__