#ifndef __SERVICE_KIND_H__
#define __SERVICE_KIND_H__
#include "simple_types.hpp"

namespace sep {
///
/// Specifies the current status of the service at this usage point.
///
enum class ServiceKind : UInt8 {
  kElectricity,
  kGas,
  kWater,
  KTime,
  kPressure,
  kHeat,
  kCooling
};
} // namespace sep

#endif // __SERVICE_KIND_H__
