#ifndef __SUBSCRIBABLE_IDENTIFIED_OBJECT_H__
#define __SUBSCRIBABLE_IDENTIFIED_OBJECT_H__
#include "simple_types.hpp"
#include "subscribable_resource.hpp"


namespace sep
{
    // An IdentifiedObject to which a Subscription can be requested.
    struct SubscribableIdentifiedObject : SubscribableResource
    {
        mRIDType mrid;
        std::string description;
        VersionType version;
    };
    
} // namespace sep

#endif // __SUBSCRIBABLE_IDENTIFIED_OBJECT_H__