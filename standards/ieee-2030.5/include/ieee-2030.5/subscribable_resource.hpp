#ifndef __SUBSCRIBABLE_RESOURCE_H__
#define __SUBSCRIBABLE_RESOURCE_H__
#include "simple_types.hpp"
#include "subscribable_type.hpp"

namespace sep
{
    // A Resource to which a Subscription can be requested.
    struct SubscribableResource : Resource
    {
        SubscribableType subscribable;
    };

    struct SubscribableList : SubscribableResource {
        UInt32 all;
    };
};     // namespace sep
#endif // __SUBSCRIBABLE_RESOURCE_H__