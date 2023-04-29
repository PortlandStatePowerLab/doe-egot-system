#include "include/world/sep_support_module.hpp"
#include <ieee-2030.5/version_information.hpp>
#include <ieee-2030.5/device_capability.hpp>
#include <ieee-2030.5/function_set_assignments.hpp>
#include <ieee-2030.5/end_device.hpp>
#include <ieee-2030.5/self_device.hpp>
#include <ieee-2030.5/response.hpp>

namespace sep
{
    
SupportModule::SupportModule(flecs::world& ecs) 
{
    /* Register module with world */
    ecs.module<sep::SupportModule>();

    /* Register components */
    ecs.component<sep::VersionInformation>();
    ecs.component<sep::DeviceCapability>();
    ecs.component<sep::FunctionSetAssignments>();
    ecs.component<sep::EndDevice>();
    ecs.component<sep::SelfDevice>();
    ecs.component<sep::Response>();

    /* Register system */    
}

} // namespace sep


