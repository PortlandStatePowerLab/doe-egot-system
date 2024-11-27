#ifndef __ROLE_FLAGS_TYPE_H__
#define __ROLE_FLAGS_TYPE_H__
#include "simple_types.hpp"

namespace sep {
///
/// Specifies the roles that apply to a usage point.
///
enum class RoleFlagsType : UInt16 {
  kIsMirror = 1 << 0,
  kIsPremisesAggregationPoint = 1 << 1,
  kIsPEV = 1 << 2,
  kIsDER = 1 << 3,
  kIsRevenueQuality = 1 << 4,
  kIsDC = 1 << 5,
  kIsSubmeter = 1 << 6
};

} // namespace sep

#endif // __ROLE_FLAGS_TYPE_H__
