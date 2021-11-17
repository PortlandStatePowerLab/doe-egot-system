#ifndef __SUBSCRIBABLE_IDENTIFIED_OBJECT_H__
#define __SUBSCRIBABLE_IDENTIFIED_OBJECT_H__
#include <string>
#include "subscribable_resource.hpp"
#include "mrid_type.hpp"
#include "version_type.hpp"

namespace sep
{
    // An IdentifiedObject to which a Subscription can be requested.
    struct SubscribableIdentifiedObject : SubscribableResource
    {
        MRIDType mrid;
        std::string description;
        VersionType version;
    };
    
} // namespace sep

#endif // __SUBSCRIBABLE_IDENTIFIED_OBJECT_H__