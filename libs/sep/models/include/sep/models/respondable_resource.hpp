#ifndef __RESPONDABLE_RESOURCE_H__
#define __RESPONDABLE_RESOURCE_H__
#include <string>
#include "simple_types.hpp"

namespace sep
{
    // A Resource to which a Response can be requested.
    struct RespondableResource : Resource
    {
        enum class ResponseRequired : HexBinary8
        {
            kRecieved,
            kSpecificResponse,
            kResponseRequired
        };
        std::string reply_to;
        ResponseRequired response_required;
    };
};     // namespace sep
#endif // __RESPONDABLE_RESOURCE_H__