#ifndef __DEVICE_CAPABILITY_H__
#define __DEVICE_CAPABILITY_H__
#include "end_device.hpp"
#include "function_set_assignments_base.hpp"
#include "mirror_usage_point.hpp"
#include "self_device.hpp"
#include "simple_types.hpp"
#include <boost/optional.hpp>

namespace sep {
struct DeviceCapabilityLink : Link {};

///
/// Returned by the URI provided by DNS-SD, to allow clients to find the URIs
/// to the resources in which they are interested.
///
struct DeviceCapability : FunctionSetAssignmentsBase {
  UInt32 poll_rate = 900;
  boost::optional<EndDeviceListLink> end_device_list_link;
  boost::optional<MirrorUsagePointListLink> mirror_usage_point_list_link;
  boost::optional<SelfDeviceLink> self_device_link;
};
} // namespace sep

#endif // __DEVICE_CAPABILITY_H__
