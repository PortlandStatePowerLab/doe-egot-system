#ifndef __POWER_FACTOR_H__
#define __POWER_FACTOR_H__
#include "simple_types.hpp"

namespace sep {
///
/// Specifies a setpoint for Displacement Power Factor, the ratio between
/// apparent and active powers at the fundamental frequency (e.g. 60 Hz).
///
struct PowerFactor {
  UInt16 displacement;
  PowerOfTenMultiplierType multiplier;
};

} // namespace sep

#endif // __POWER_FACTOR_H__
