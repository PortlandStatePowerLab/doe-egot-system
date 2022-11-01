#ifndef __SERVER_SEP_COMMON_MODULE_H__
#define __SERVER_SEP_COMMON_MODULE_H__

#include <flecs.h>


namespace sep
{
    struct CommonModule
    {
        CommonModule(flecs::world& ecs);
    };
} // namespace sep



#endif // __SERVER_SEP_COMMON_MODULE_H__