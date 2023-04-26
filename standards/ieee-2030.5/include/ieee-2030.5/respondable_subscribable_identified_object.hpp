#ifndef __RESPONDABLE_SUBSCRIBABLE_IDENTIFIED_OBJECT_H__
#define __RESPONDABLE_SUBSCRIBABLE_IDENTIFIED_OBJECT_H__
#include "simple_types.hpp"
#include "respondable_resource.hpp"
#include "subscribable_type.hpp"

namespace sep
{
    // An IdentifiedObject to which a Response can be requested.
    struct RespondableSubscribableIdentifiedObject : RespondableResource
    {
        mRIDType mrid;
        String32 description;
        VersionType version;
        SubscribableType subscribable;
    };
};     // namespace sep
#endif // __RESPONDABLE_SUBSCRIBABLE_IDENTIFIED_OBJECT_H__