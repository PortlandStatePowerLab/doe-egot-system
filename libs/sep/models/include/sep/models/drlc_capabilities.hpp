#ifndef __DRLC_CAPABILITIES_H__
#define __DRLC_CAPABILITIES_H__
#include "active_power.hpp"
#include "real_energy.hpp"
#include "simple_types.hpp"

namespace sep {
///
/// Contains information about the static capabilities of the device,
/// to allow service providers to know what types of functions are supported,
/// what the normal operating ranges and limits are, and other similar
/// information, in order to provide better suggestions of applicable
/// programs to receive the maximum benefit.
///
struct DRLCCapabilities {
  // Bitmap indicating the DRLC options implemented by the device.
  enum class Options : UInt32 {
    kKiloWattHours = 0 << 1,
    kKiloWatts = 0 << 2,
    kWatts = 0 << 3,
    kCubicMeters = 0 << 4,
    kCubicFeet = 0 << 5,
    kUSGallons = 0 << 6,
    kImperialGallons = 0 << 7,
    kBTUs = 0 << 8,
    kLiters = 0 << 9,
    kKiloPascalsGauge = 0 << 10,
    kKiloPascalsAbsolute = 0 << 11,
    kMegaJoule = 0 << 12,
    kUnitless = 0 << 13,
    kTemperatureSetPoint = 0 << 17,
    kTemperatureOffset = 0 << 18,
    kDutyCycle = 0 << 19,
    kLoadAdjustmentPercentage = 0 << 20,
    kApplieanceLoadReduction = 0 << 21
  };
  /* data */
};

} // namespace sep

#endif // __DRLC_CAPABILITIES_H__
