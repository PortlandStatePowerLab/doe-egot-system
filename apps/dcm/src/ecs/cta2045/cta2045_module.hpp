#ifndef __DCM_CTA2045_MODULE_H__
#define __DCM_CTA2045_MODULE_H__

#include <flecs.h>


namespace cta2045
{
    struct UniversalModule
    {
        UniversalModule(flecs::world& ecs);
    };
} // namespace sep

#endif // __DCM_CTA2045_MODULE_H__