#include "include/world/sep_common_module.hpp"
#include <ieee-2030.5/common_models.hpp>

namespace sep
{
    
    CommonModule::CommonModule(flecs::world &ecs)
    {
        /* Register module with world */
        ecs.module<CommonModule>();

        /* Register components */
        ecs.component<Time>();
        ecs.component<DeviceInformation>();
        ecs.component<PowerStatus>();
        ecs.component<Configuration>();

        /* Register system */

    };
} // namespace sep
