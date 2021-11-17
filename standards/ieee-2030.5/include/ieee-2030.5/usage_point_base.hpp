#ifndef __USAGE_POINT_BASE_H__
#define __USAGE_POINT_BASE_H__
#include "identified_object.hpp"
#include "service_kind.hpp"
#include "role_flags_type.hpp"

namespace sep
{
    // Logical point on a network at which consumption or production is either physically measured 
    // (e.g. metered) or estimated (e.g. unmetered street lights). 
    // A container for associating ReadingType, Readings and ReadingSets.
    struct UsagePointBase : IdentifiedObject
    {
        // Specifies the current status of the service at this usage point.
        enum class Status : uint8_t
        {
            kOff,
            kOn
        };

        RoleFlagsType role_flags;
        ServiceKind service_category_kind;
        Status status;
    };
    
} // namespace sep

#endif // __USAGE_POINT_BASE_H__