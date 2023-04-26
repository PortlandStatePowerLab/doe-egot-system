#ifndef __READING_H__
#define __READING_H__
#include "simple_types.hpp"
#include "reading_base.hpp"
#include "subscribable_type.hpp"

namespace sep
{
    struct ReadingListLink : ListLink {};
    struct ReadingLink : Link {};
    
    // Specific value measured by a meter or other asset.
    struct Reading : ReadingBase
    {
        Int16 local_id;
        SubscribableType subscribable;
    };
    
} // namespace sep

#endif // __READING_H__