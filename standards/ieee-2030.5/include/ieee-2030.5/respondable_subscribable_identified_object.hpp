#ifndef __RESPONDABLE_SUBSCRIBABLE_IDENTIFIED_OBJECT_H__
#define __RESPONDABLE_SUBSCRIBABLE_IDENTIFIED_OBJECT_H__
#include <string>
#include "respondable_resource.hpp"
#include "subscribable_type.hpp"

namespace sep
{
    // An IdentifiedObject to which a Response can be requested.
    struct RespondableSubscribableIdentifiedObject : RespondableResource
    {
        std::string mrid;
        std::string description;
        uint16_t version;
        sep::SubscribableType subscribable;
    };
};     // namespace sep
#endif // __RESPONDABLE_SUBSCRIBABLE_IDENTIFIED_OBJECT_H__