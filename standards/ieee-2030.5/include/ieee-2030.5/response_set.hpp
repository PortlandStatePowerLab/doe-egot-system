#ifndef __RESPONSE_SET_H__
#define __RESPONSE_SET_H__
#include "identified_object.hpp"
#include "list_link.hpp"

namespace sep
{
    // The Response object is the generic response data repository 
    // which is extended for specific function sets.
    struct ResponseSet : IdentifiedObject
    {
        ListLink response_list_link;

    };
    
} // namespace sep
#endif // __RESPONSE_SET_H__