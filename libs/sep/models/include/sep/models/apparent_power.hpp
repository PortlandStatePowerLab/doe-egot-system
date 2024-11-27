#ifndef __APPARENT_POWER_H__
#define __APPARENT_POWER_H__
#include "simple_types.hpp"

namespace sep {
///
/// The apparent power S (in VA) is
/// the product of root mean square (RMS) voltage and RMS current.
///
struct ApparentPower {
  PowerOfTenMultiplierType multiplier;
  UInt16 value;
};

} // namespace sep

#endif // __APPARENT_POWER_H__
