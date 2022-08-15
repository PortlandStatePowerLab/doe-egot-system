#include "include/world/sep_support_module.hpp"
#include <trust_gsp_client.hpp>
#include <ieee-2030.5/support_models.hpp>
#include <xml/adapter.hpp>
#include <utilities/utilities.hpp>


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
    ecs.component<sep::SelfDevice>();
    ecs.component<sep::Response>();

    /* Register system */    
    ecs.system<sep::DeviceCapability>("dcap")
        .iter([&](flecs::iter it, sep::DeviceCapability* dcap) {    
            if (dcap->poll_rate % psu::utilities::getTime() == 0)
            {
                for (int i : it)
                {
                    auto resp = GSPClient::getInstance()->Get("/dcap");
                    std::string msg = boost::beast::buffers_to_string(resp.body().data());
                    xml::Parse(msg, dcap[i]);
                }
            }
        });
}

} // namespace sep


