#ifndef __SUBSCRIBABLE_RESOURCE_H__
#define __SUBSCRIBABLE_RESOURCE_H__
#include "simple_types.hpp"
#include "subscribable_type.hpp"
#include <boost/optional.hpp>

namespace sep
{
    // A Resource to which a Subscription can be requested.
    struct SubscribableResource : Resource
    {
        boost::optional<SubscribableType> subscribable;
    };

    struct SubscribableList : SubscribableResource {
        UInt32 all;
        UInt32 results;
    };
};     // namespace sep
#endif // __SUBSCRIBABLE_RESOURCE_H__