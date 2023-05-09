#ifndef __LOG_EVENT_H__
#define __LOG_EVENT_H__
#include "simple_types.hpp"
#include "pen_type.hpp"

namespace sep {
    struct LogEventListLink : ListLink {};
    struct LogEventLink : Link {};

    // A time stamped instance of a significant event detected by the device.
    struct LogEvent : Resource {
        enum class FunctionSet : UInt8{
            GENERAL,
            PUB_SUB,
            END_DEVICE,
            FSA,
            RESPONSE,
            DRLC,
            METERING,
            PRICING,
            MESSAGING,
            BILLING,
            PREPAYMENT,
            DER,
            TIME,
            SOFTWARE_DOWNLOAD,
            DEVICE_INFO,
            POWER_STATUS,
            NETWORK_STATUS,
            LOG_EVENT_LIST,
            CONFIGURATION,
            SECURITY
        };

        enum class ProfileID : UInt8 {
            NOT_PROFILE_SPECIFIC,
            VENDOR_DEFINED,
            IEEE_2030_5,
            HOME_AUTOMATION,
            BUILDING_AUTOMATION
        };

        TimeType created_date_time;
        String32 details;
        UInt32 extended_data;
        FunctionSet function_set;
        UInt8 log_event_code;
        UInt16 log_event_id;
        PENType log_event_pen;
        ProfileID profile_id; 
    };
}

#endif // __LOG_EVENT_H__