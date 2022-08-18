#include "include/cta2045_module.hpp"
#include "include/sep_support_module.hpp"
#include <ieee-2030.5/models.hpp>
#include <trust_der_client.hpp>
#include <trust_gsp_client.hpp>
#include <xml/adapter.hpp>

namespace cta2045
{
    UniversalModule::UniversalModule (flecs::world &ecs)
    {
        /* Register module with world */
        ecs.module<UniversalModule>();
        ecs.module<sep::SupportModule>();

        /* Register components */
        ecs.component<cea2045::cea2045CommodityData>();

        /* Register system */
        ecs.system<cea2045::cea2045CommodityData>("EnergyTake")
            .each([&](flecs::entity e, const cea2045::cea2045CommodityData &data) {    
                if((uint64_t)data.instantaneousRate >= 1200)
                {
                    sep::FlowReservationRequest frr;
                    auto resp = TrustGSPClient::getInstance()->Post("/frr", xml::Serialize(frr));
                    std::string msg = boost::beast::buffers_to_string(resp.body().data());
                    ecs.entity().add<sep::FlowReservationRequest>();
                    
                }
            });        
    }
} // namespace cta2045
