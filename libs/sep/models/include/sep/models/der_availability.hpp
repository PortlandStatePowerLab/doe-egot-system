#ifndef __DER_AVAILABILITY_H__
#define __DER_AVAILABILITY_H__
#include "active_power.hpp"
#include "per_cent.hpp"
#include "reactive_power.hpp"
#include "simple_types.hpp"
#include "subscribable_resource.hpp"

namespace sep {
struct DERAvailabilityLink : Link {};

///
/// Indicates current reserve generation status
///
struct DERAvailability : SubscribableResource {
  UInt32 availability_duration;
  UInt32 max_charge_duration;
  TimeType reading_time;
  PerCent reserve_charge_percent;
  PerCent reserve_percent;
  ReactivePower stat_var_avail;
  ActivePower stat_w_avail;
};

} // namespace sep

#endif // __DER_AVAILABILITY_H__
