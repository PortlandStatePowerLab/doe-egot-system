#ifndef __LIST_H__
#define __LIST_H__
#include <cstdint>
#include "resource.hpp"

namespace sep
{
    // Container to hold a collection of object instances or references. 
    // See Design Pattern section for additional details.
    struct List : sep::Resource
    {
        uint32_t all;
        uint32_t results;
    };
    
} // namespace sep

#endif // __LIST_H__