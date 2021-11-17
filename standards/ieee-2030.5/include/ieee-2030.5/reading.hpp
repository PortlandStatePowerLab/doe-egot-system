#ifndef __READING_H__
#define __READING_H__
#include "reading_base.hpp"
#include "subscribable_type.hpp"

namespace sep
{
    // Specific value measured by a meter or other asset.
    struct Reading : ReadingBase
    {
        uint16_t local_id;
        SubscribableType subscribable;
    };
    
} // namespace sep

#endif // __READING_H__