#ifndef __RESOURCE_H__
#define __RESOURCE_H__
#include <string>

namespace sep
{
    //  resource is an addressable unit of information, either
    // a collection (List) or instance of an object.
    struct Resource
    {
        std::string href; // optional
        uint32_t inherited_poll_rate;
    };
}; // namespace sep

#endif // __RESOURCE_H__