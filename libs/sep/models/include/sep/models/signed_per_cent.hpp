#ifndef __SIGNED_PER_CENT_H__
#define __SIGNED_PER_CENT_H__
#include "simple_types.hpp"

namespace sep {
///
/// Used for signed percentages, specified in hundredths of a percent,
/// -10000 to 10000. (10000 = 100%)
///
using SignedPerCent = UInt16;
};     // namespace sep
#endif // __SIGNED_PER_CENT_H__
