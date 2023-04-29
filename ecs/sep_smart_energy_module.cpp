#include "include/world/sep_smart_energy_module.hpp"
#include <ieee-2030.5/flow_reservation_request.hpp>
#include <ieee-2030.5/flow_reservation_response.hpp>
#include <ieee-2030.5/flow_reservation_response_response.hpp>
#include <ieee-2030.5/mirror_meter_reading.hpp>
#include <ieee-2030.5/der.hpp>

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