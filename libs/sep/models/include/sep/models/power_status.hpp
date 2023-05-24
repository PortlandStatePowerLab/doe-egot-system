#ifndef __POWER_STATUS_H__
#define __POWER_STATUS_H__

#include "per_cent.hpp"
#include "pev_info.hpp"
#include "power_source_type.hpp"
#include "simple_types.hpp"
#include <boost/optional.hpp>

namespace sep {
enum class BatteryStatus : UInt8 { kUnknown, kNormal, kLow, kDepleted, kNA };

struct PowerStatusListLink : ListLink {};
struct PowerStatusLink : Link {};

// Contains the status of the device's power sources
struct PowerStatus : Resource {
  BatteryStatus battery_status;
  TimeType changed_time;
  PowerSourceType current_power_source;
  UInt32 poll_rate;
  boost::optional<PerCent> estimated_charge_remaining;
  boost::optional<UInt32> estimated_time_remaining;
  boost::optional<PEVInfo> pev_info;
  boost::optional<UInt32> session_time_on_battery;
  boost::optional<UInt32> total_time_on_battery;
};

} // namespace sep

#endif // __POWER_STATUS_H__