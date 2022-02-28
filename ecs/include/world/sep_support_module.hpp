#ifndef __SEP_SUPPORT_MODULE_H__
#define __SEP_SUPPORT_MODULE_H__

#include <flecs.h>

namespace sep
{
    struct SupportModule
    {
    public:
        SupportModule(flecs::world &ecs);
    };
} // namespace sep

#endif // __SEP_SUPPORT_MODULE_H__