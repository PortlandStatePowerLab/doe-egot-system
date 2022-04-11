#ifndef __RESPONSE_H__
#define __RESPONSE_H__
#include <boost/multiprecision/cpp_int.hpp>
#include <cstdint>
#include "resource.hpp"
#include "list_link.hpp"
#include "time_type.hpp"
#include "mrid_type.hpp"

namespace sep
{
    // A container for a ResponseList
    struct Response : Resource
    {
        enum class Status : uint8_t
        {
            kEventReceived = 1,
            kEventStarted = 2,
            kEventComplete = 3,
            kOptOut = 4,
            kOptIn = 5,
            kCancelled = 6,
            kSuperseded = 7,
            kPartiallyCompletedOptOut = 8,
            kPartiallyCompletedOptIn = 9,
            kEventCompleteNoParticipation = 10,
            kEventAcknowledged = 11,
            kCannotBeDisplayed = 12,
            kEventAbortedAlternateServerEvent = 13,
            kEventAbortedAlternateProgramEvent = 14,
            kRejectedParamaterNA = 252,
            kRejectedInvalidEvent = 253,
            kRejectedExpired = 254
        };

        sep::TimeType created_date_time;
        boost::multiprecision::uint256_t end_device_lfdi;
        Status status;
        MRIDType subject;
    };
    
} // namespace sep

#endif // __RESPONSE_H__