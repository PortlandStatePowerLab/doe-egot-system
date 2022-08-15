#include "include/world/sep_smart_energy_module.hpp"
#include <ieee-2030.5/smart_energy_models.hpp>

namespace sep
{
    SmartEnergyModule::SmartEnergyModule (flecs::world& ecs)
    {
        /* Register module with world */
        ecs.module<SmartEnergyModule>();

        /* Register components */
        ecs.component<FlowReservationRequest>();
        ecs.component<FlowReservationResponse>();
        ecs.component<FlowReservationResponseResponse>();
        ecs.component<MirrorMeterReading>();
        ecs.component<DER>();

        /* Register system */
    };    
} // namespace sep