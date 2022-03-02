#ifndef __RESPONDABLE_SUBSCRIBABLE_IDENTIFIED_OBJECT_H__
#define __RESPONDABLE_SUBSCRIBABLE_IDENTIFIED_OBJECT_H__
#include <string>
#include "respondable_resource.hpp"
#include "subscribable_type.hpp"
#include "mrid_type.hpp"

namespace sep
{
    // An IdentifiedObject to which a Response can be requested.
    struct RespondableSubscribableIdentifiedObject : RespondableResource
    {
        MRIDType mrid;
        std::string description;
        uint16_t version;
        SubscribableType subscribable;
    };
};     // namespace sep
#endif // __RESPONDABLE_SUBSCRIBABLE_IDENTIFIED_OBJECT_H__