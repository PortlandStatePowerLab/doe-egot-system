#ifndef __FLOW_RESERVATION_RESPONSE_H__
#define __FLOW_RESERVATION_RESPONSE_H__
#include "simple_types.hpp"
#include "event.hpp"
#include "signed_real_energy.hpp"
#include "active_power.hpp"

namespace sep
{
    struct FlowReservationResponseListLink : ListLink {};
    struct FlowReservationResponseLink : Link {};
    
    // The server may modify the charging or discharging parameters and interval
    // to provide a lower aggregated demand at the premises, or within a larger
    // part of the distribution system.
    struct FlowReservationResponse : Event
    {
        SignedRealEnergy energy_available; // energy in watt-hours
        ActivePower power_available;       // power in watts
        mRIDType subject;               // match event
    };
};     // namespace sep
#endif // __FLOW_RESERVATION_RESPONSE_H__