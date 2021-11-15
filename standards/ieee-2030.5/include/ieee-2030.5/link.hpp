#ifndef __LINK_H__
#define __LINK_H__
#include <string>

namespace sep
{
    // Links provide a reference, via URI, to another resource.
    struct Link
    {
        std::string href;
    };
} // namespace sep

#endif // __LINK_H__