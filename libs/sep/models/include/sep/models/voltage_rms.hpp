#ifndef __VOLTAGE_RMS_H__
#define __VOLTAGE_RMS_H__
#include "simple_types.hpp"

namespace sep {
///
/// Average electric potential difference between two points.
///
struct VoltageRMS {
  PowerOfTenMultiplierType multiplier;
  UInt16 value;
};

} // namespace sep

#endif // __VOLTAGE_RMS_H__
