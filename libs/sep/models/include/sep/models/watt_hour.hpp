#ifndef __WATT_HOUR_H__
#define __WATT_HOUR_H__
#include "simple_types.hpp"

namespace sep {
///
/// Active (real) energy
///
struct WattHour {
  PowerOfTenMultiplierType multiplier;
  UInt16 value;
};

} // namespace sep

#endif // __WATT_HOUR_H__
