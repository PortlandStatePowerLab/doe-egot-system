#ifndef __FLOW_RESERVATION_REQUEST_H__
#define __FLOW_RESERVATION_REQUEST_H__
#include <vector>
#include "simple_types.hpp"
#include "signed_real_energy.hpp"
#include "date_time_interval.hpp"
#include "active_power.hpp"
#include "request_status.hpp"
#include "subscribable_resource.hpp"
namespace sep
{
    struct FlowReservationRequestListLink : ListLink {};
    struct FlowReservationRequestLink : Link {};

    // Used to request flow transactions. Client EndDevices submit a request for
    // charging or discharging from the server. The server creates an associated
    // FlowReservationResponse containing the charging parameters and interval to
    // provide a lower aggregated demand at the premises, or within a larger part
    // of the distribution system
    struct FlowReservationRequest : IdentifiedObject
    {
        TimeType creation_time;
        UInt16 duration_requested;
        SignedRealEnergy energy_requested;
        DateTimeInterval interval_requested;
        ActivePower power_requested;
        RequestStatus request_status;
    };

    struct FlowReservationRequestList : SubscribableList {
        std::vector<FlowReservationRequest> flow_reservation_requests;
        UInt32 poll_rate;
    };
} // namespace sep

#endif // __FLOW_RESERVATION_REQUEST_H__