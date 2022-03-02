#ifndef __RESPONDABLE_RESOURCE_H__
#define __RESPONDABLE_RESOURCE_H__
#include <cstdint>
#include <string>
#include "resource.hpp"

namespace sep
{
    // A Resource to which a Response can be requested.
    struct RespondableResource : Resource
    {
        enum class ResponseRequired : uint8_t
        {
            kRecieved,
            kSpecificResponse,
            kResponseRequired
        };

        Resource resource;
        std::string reply_to;
        ResponseRequired response_required;
    };
};     // namespace sep
#endif // __RESPONDABLE_RESOURCE_H__