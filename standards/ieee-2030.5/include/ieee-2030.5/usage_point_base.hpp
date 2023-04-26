#ifndef __USAGE_POINT_BASE_H__
#define __USAGE_POINT_BASE_H__
#include "simple_types.hpp"
#include "service_kind.hpp"
#include "role_flags_type.hpp"
#include "meter_reading_base.hpp"

namespace sep
{
    // Logical point on a network at which consumption or production is either physically measured 
    // (e.g. metered) or estimated (e.g. unmetered street lights). 
    // A container for associating ReadingType, Readings and ReadingSets.
    struct UsagePointBase : IdentifiedObject
    {
        // Specifies the current status of the service at this usage point.
        enum class Status : UInt8
        {
            kOff,
            kOn
        };

        RoleFlagsType role_flags;
        ServiceKind service_category_kind;
        Status status;
    };

    struct UsagePointListLink : ListLink {};
    struct UsagePointLink : Link {};

    // Logical point on a network at which consumption or production is 
    // either physically measured (e.g. metered) or estimated 
    // (e.g. unmetered street lights).
    struct UsagePoint : UsagePointBase {
        HexBinary160 device_lfdi;
        MeterReadingListLink meter_reading_list_link;
    };
    
} // namespace sep

#endif // __USAGE_POINT_BASE_H__