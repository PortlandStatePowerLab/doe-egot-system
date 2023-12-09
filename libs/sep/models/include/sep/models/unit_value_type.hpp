#ifndef __UNIT_VALUE_TYPE_H__
#define __UNIT_VALUE_TYPE_H__
#include "simple_types.hpp"
#include "uom_type.hpp"

namespace sep {
///
/// Type for specification of a specific value,
/// with units and power of ten multiplier.
///
struct UnitValueType {
  PowerOfTenMultiplierType multiplier;
  UomType unit;
  Int32 value;
};

} // namespace sep

#endif // __UNIT_VALUE_TYPE_H__
