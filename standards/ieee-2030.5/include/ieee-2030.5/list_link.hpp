#ifndef __LIST_LINK_H__
#define __LIST_LINK_H__
#include <cstdint>
#include "link.hpp"

namespace sep
{
    // ListLinks provide a reference, via URI, to a List
    struct ListLink : sep::Link
    {
        uint32_t all; // optional
    };

} // namespace sep

#endif // __LIST_LINK_H__