#include "include/world/sep_support_module.hpp"
#include <ieee-2030.5/support_models.hpp>

namespace sep
{
    
SupportModule::SupportModule(flecs::world& ecs) 
{
    /* Register module with world */
    ecs.module<sep::SupportModule>();

    /* Register components */
    ecs.component<sep::VersionInformation>();
    ecs.component<sep::DeviceCapability>();
    ecs.component<sep::FunctionSetAssignmentsBase>();
    ecs.component<sep::EndDevice>();

    /* Register system */
    
}

} // namespace sep


