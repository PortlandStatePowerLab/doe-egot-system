#ifndef __SERVER_SEP_SMART_ENERGY_MODULE_H__
#define __SERVER_SEP_SMART_ENERGY_MODULE_H__

#include <flecs.h>

namespace sep
{
    struct SmartEnergyModule
    {
        SmartEnergyModule(flecs::world &ecs);
    };
} // namespace sep

#endif // __SEP_SMART_ENERGY_MODULE_H__