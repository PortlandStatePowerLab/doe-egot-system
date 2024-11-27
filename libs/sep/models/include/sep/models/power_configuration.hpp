#ifndef __POWER_CONFIGURATION_H__
#define __POWER_CONFIGURATION_H__

#include "simple_types.hpp"

namespace sep {
///
/// Contains configuration related to the device's power sources
///
struct PowerConfiguration {
  TimeType battery_install_time;
  UInt32 low_charge_threshold;
};

} // namespace sep

#endif // __POWER_CONFIGURATION_H__
