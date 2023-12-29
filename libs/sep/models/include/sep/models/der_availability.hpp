#ifndef __DER_AVAILABILITY_H__
#define __DER_AVAILABILITY_H__
#include "active_power.hpp"
#include "per_cent.hpp"
#include "reactive_power.hpp"
#include "simple_types.hpp"
#include "subscribable_resource.hpp"
#include <boost/optional.hpp>

namespace sep {
struct DERAvailabilityLink : Link {};

///
/// Indicates current reserve generation status
///
struct DERAvailability : SubscribableResource {
  boost::optional<UInt32> availability_duration;
  boost::optional<UInt32> max_charge_duration;
  TimeType reading_time;
  boost::optional<PerCent> reserve_charge_percent;
  boost::optional<PerCent> reserve_percent;
  boost::optional<ReactivePower> stat_var_avail;
  boost::optional<ActivePower> stat_w_avail;
};

} // namespace sep

#endif // __DER_AVAILABILITY_H__
