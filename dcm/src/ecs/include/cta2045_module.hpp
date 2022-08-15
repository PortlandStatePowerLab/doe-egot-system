#ifndef __CTA2045_MODULE_H__
#define __CTA2045_MODULE_H__

#include <flecs.h>


namespace cta2045
{
    struct UniversalModule
    {
        UniversalModule(flecs::world& ecs);
    };
} // namespace sep

#endif // __CTA2045_MODULE_H__