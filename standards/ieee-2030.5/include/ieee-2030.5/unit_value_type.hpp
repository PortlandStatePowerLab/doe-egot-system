#ifndef __UNIT_VALUE_TYPE_H__
#define __UNIT_VALUE_TYPE_H__
#include <cstdint>
#include "power_of_ten_multiplier_type.hpp"
#include "uom_type.hpp"

namespace sep
{
    // Type for specification of a specific value, 
    // with units and power of ten multiplier.
    struct UnitValueType
    {
        PowerOfTenMultiplierType multiplier;
        UomType unit;
        int32_t value;
    };
    
} // namespace sep

#endif // __UNIT_VALUE_TYPE_H__