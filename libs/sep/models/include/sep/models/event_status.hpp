#ifndef __EVENT_STATUS_H__
#define __EVENT_STATUS_H__
#include "simple_types.hpp"
#include "date_time_interval.hpp"

namespace sep
{
    // Current status information relevant to a specific object.
    // The Status object is used to indicate the current status of an Event.
    // Devices can read the containing resource (e.g. TextMessage) to get
    // the most up to date status of the event.  Devices can also subscribe
    // to a specific resource instance to get updates when any of its
    // attributes change, including the Status object.
    struct EventStatus
    {
        enum class CurrentStatus : UInt8
        {
            kScheduled,
            kActive,
            kCancelled,
            kCancelledWithRandomization,
            kSuperseded
        };

        CurrentStatus current_status;
        TimeType date_time;
        bool potentially_superseded;
        TimeType potentially_superseded_time;
        String192 reason;
    };
};     // namespace sep
#endif // __EVENT_STATUS_H__