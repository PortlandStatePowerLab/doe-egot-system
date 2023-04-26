#ifndef __RESPONSE_SET_H__
#define __RESPONSE_SET_H__
#include "simple_types.hpp"
#include "response.hpp"

namespace sep
{
    struct ResponseSetListLink : ListLink {};
    struct ReponseSetLink : Link {};
    
    // The Response object is the generic response data repository 
    // which is extended for specific function sets.
    struct ResponseSet : IdentifiedObject
    {
        ResponseListLink response_list_link;

    };
    
} // namespace sep
#endif // __RESPONSE_SET_H__