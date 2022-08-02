#include "include/world/cta2045_module.hpp"

namespace cta2045
{
    UniversalModule::UniversalModule (flecs::world &ecs)
    {
        /* Register module with world */
        ecs.module<CommonModule>();

        /* Register components */
        ecs.component<Time>();
        ecs.component<DeviceInformation>();
        ecs.component<PowerStatus>();
        ecs.component<Configuration>();

        /* Register system */
    }
} // namespace cta2045
