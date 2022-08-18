#ifndef __DCM_SEP_SUPPORT_MODULE_H__
#define __DCM_SEP_SUPPORT_MODULE_H__

#include <flecs.h>

namespace sep
{
    struct SupportModule
    {
    public:
        SupportModule(flecs::world &ecs);
    };
} // namespace sep

#endif // __DCM_SEP_SUPPORT_MODULE_H__