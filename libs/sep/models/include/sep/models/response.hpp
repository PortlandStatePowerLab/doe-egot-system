#ifndef __RESPONSE_H__
#define __RESPONSE_H__
#include <vector>
#include "simple_types.hpp"
#include "subscribable_resource.hpp"
namespace sep
{
    struct ResponseListLink : ListLink {};
    struct ResponseLink : Link {};

    // The Response object is the generic response data repository which is 
    // extended for specific function sets.
    struct Response : Resource
    {
        enum class Status : UInt8
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

        TimeType created_date_time;
        HexBinary160 end_device_lfdi;
        Status status;
        mRIDType subject;
    };

    struct ResponseList : List {
        std::vector<Response> responses;
    };
    
} // namespace sep

#endif // __RESPONSE_H__