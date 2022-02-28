#ifndef __SEP_COMMON_MODULE_H__
#define __SEP_COMMON_MODULE_H__

#include <flecs.h>


namespace sep
{
    struct CommonModule
    {
        CommonModule(flecs::world& ecs);
    };
} // namespace sep



#endif // __SEP_COMMON_MODULE_H__