#ifndef __SUBSCRIBABLE_RESOURCE_H__
#define __SUBSCRIBABLE_RESOURCE_H__
#include <cstdint>
#include "resource.hpp"
#include "subscribable_type.hpp"

namespace sep
{
    // A Resource to which a Subscription can be requested.
    struct SubscribableResource : Resource
    {
        sep::SubscribableType subscribable;
    };
};     // namespace sep
#endif // __SUBSCRIBABLE_RESOURCE_H__