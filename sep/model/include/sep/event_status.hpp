#ifndef __EVENT_STATUS_H__
#define __EVENT_STATUS_H__
#include <cstdint>
#include <string>
#include "time_type.hpp"
#include "date_time_interval.hpp"

namespace sep
{
    enum class CurrentStatus : uint8_t
    {
        kScheduled,
        kActive,
        kCancelled,
        kCancelledWithRandomization,
        kSuperseded
    };

    // Current status information relevant to a specific object.
    // The Status object is used to indicate the current status of an Event.
    // Devices can read the containing resource (e.g. TextMessage) to get
    // the most up to date status of the event.  Devices can also subscribe
    // to a specific resource instance to get updates when any of its
    // attributes change, including the Status object.
    struct EventStatus
    {
        sep::CurrentStatus current_status;
        sep::TimeType date_time;
        bool potentially_superseded;
        sep::TimeType potentially_superseded_time;
        std::string reason;
    };
};     // namespace sep
#endif // __EVENT_STATUS_H__