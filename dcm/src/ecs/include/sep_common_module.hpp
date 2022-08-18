#ifndef __DCM_SEP_COMMON_MODULE_H__
#define __DCM_SEP_COMMON_MODULE_H__

#include <flecs.h>


namespace sep
{
    struct CommonModule
    {
        CommonModule(flecs::world& ecs);
    };
} // namespace sep



#endif // __DCM_SEP_COMMON_MODULE_H__