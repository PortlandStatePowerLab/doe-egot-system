#include "include/cta2045_module.hpp"
#include <ieee-2030.5/models.hpp>
#include <cta2045/ucm.hpp>
#include <trust_der_client.hpp>
#include <trust_gsp_client.hpp>

namespace cta2045
{
    UniversalModule::UniversalModule (flecs::world &ecs)
    {
        /* Register module with world */
        ecs.module<UniversalModule>();

        /* Register components */
        ecs.component<cea2045::cea2045CommodityData>();

        /* Register system */
        ecs.system<cea2045::cea2045CommodityData>("EnergyTake")
            .iter([&](flecs::iter it, const cea2045::cea2045CommodityData &data) {    
                
                if((int)data.instantaneousRate >= 1200)
                {
                    sep::FlowReservationRequest frr;
                    auto resp = GSPClient::getInstance()->Post("/frr", frr);
                    std::string msg = boost::beast::buffers_to_string(resp.body().data());
                    xml::Parse(msg, dcap[i]);
                    ecs.entity().add<sep::FlowReservationRequest>();
                }
            });        
    }
} // namespace cta2045
