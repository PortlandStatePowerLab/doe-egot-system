#ifndef __END_DEVICE_H__
#define __END_DEVICE_H__
#include "abstract_device.hpp"
#include "flow_reservation_request.hpp"
#include "flow_reservation_response.hpp"
#include "function_set_assignments.hpp"
#include "registration.hpp"
#include "simple_types.hpp"
#include "subscribable_resource.hpp"
#include "subscription.hpp"
#include <boost/optional.hpp>
#include <vector>

namespace sep {
struct EndDeviceListLink : ListLink {};
struct EndDeviceLink : Link {};

///
/// Asset container that performs one or more end device functions.
/// Contains information about individual devices in the network.
///
struct EndDevice : AbstractDevice {
  TimeType changed_time;
  boost::optional<bool> enabled;
  boost::optional<FlowReservationRequestListLink>
      flow_reservation_request_list_link;
  boost::optional<FlowReservationResponseListLink>
      flow_reservation_response_list_link;
  boost::optional<FunctionSetAssignmentsListLink>
      function_set_assignments_list_link;
  boost::optional<UInt32> post_rate;
  boost::optional<RegistrationLink> registration_link;
  boost::optional<SubscriptionListLink> subscription_list_link;
};

struct EndDeviceList : SubscribableList {
  std::vector<EndDevice> end_devices;
  UInt32 poll_rate;
};

} // namespace sep

#endif // __END_DEVICE_H__
