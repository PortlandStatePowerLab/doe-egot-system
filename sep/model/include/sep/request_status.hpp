#ifndef __REQUEST_STATUS_H__
#define __REQUEST_STATUS_H__
#include <cstdint>
#include "time_type.hpp"


namespace sep
{
    // Field representing the request status type.
    enum class Status : uint8_t
    {
        kRequested,
        kCancelled
    };

    // The RequestStatus object is used to indicate the current status of a Flow Reservation Request.
    struct RequestStatus
    {
        sep::TimeType datetime;
        Status status;
    };
} // namespace sep

#endif // __REQUEST_STATUS_H__