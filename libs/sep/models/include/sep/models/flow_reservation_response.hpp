#ifndef __FLOW_RESERVATION_RESPONSE_H__
#define __FLOW_RESERVATION_RESPONSE_H__
#include "active_power.hpp"
#include "event.hpp"
#include "signed_real_energy.hpp"
#include "simple_types.hpp"
#include "subscribable_resource.hpp"
#include <vector>

namespace sep {
struct FlowReservationResponseListLink : ListLink {};
struct FlowReservationResponseLink : Link {};

///
/// The server may modify the charging or discharging parameters and interval
/// to provide a lower aggregated demand at the premises, or within a larger
/// part of the distribution system.
///
struct FlowReservationResponse : Event {
  SignedRealEnergy energy_available; // energy in watt-hours
  ActivePower power_available;       // power in watts
  mRIDType subject;                  // match event
};

struct FlowReservationResponseList : SubscribableList {
  std::vector<FlowReservationResponse> flow_reservation_responses;
  UInt32 poll_rate;
};
};     // namespace sep
#endif // __FLOW_RESERVATION_RESPONSE_H__
