#ifndef __DCM_SEP_SMART_ENERGY_MODULE_H__
#define __DCM_SEP_SMART_ENERGY_MODULE_H__

#include <flecs.h>

namespace sep
{
    struct SmartEnergyModule
    {
        SmartEnergyModule(flecs::world &ecs);
    };
} // namespace sep

#endif // __DCM_SEP_SMART_ENERGY_MODULE_H__