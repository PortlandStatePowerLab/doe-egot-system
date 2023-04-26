#include "include/sep/dcap.hpp"
#include "include/sep/fsa.hpp"
#include <iostream>
#include <trust_https/trust_https.hpp>

namespace sep {
namespace dcap {

Module::Module(flecs::world& world){
    world.module<Module>();

    world.component<Test>();
    world.component<Link>();
    world.component<EndDeviceListLink>();
    world.component<MirrorUsagePointListLink>();
    world.component<SelfDeviceLink>();
    world.component<PollRate>();

    // world.prefab<DeviceCapability>().is_a<fsab::FunctionSetAssignmentsBase>();
    // world.prefab<Link>().slot_of<DeviceCapability>();
    // world.prefab<EndDeviceListLink>().slot_of<DeviceCapability>();
    // world.prefab<MirrorUsagePointListLink>().slot_of<DeviceCapability>();
    // world.prefab<SelfDeviceLink>().slot_of<DeviceCapability>();
    // world.prefab<PollRate>().slot_of<DeviceCapability>();

    world.system<PollRate, EndDeviceListLink>("update edev")
        .each([](flecs::entity e, PollRate& poll, EndDeviceListLink& edev){
            poll.seconds--;
            if (poll.seconds == 0){
                auto resp = trust::HttpsClient::getInstance().Get(edev.href);
                std::cout << resp << std::endl;
                poll.seconds = 5;
            }
        });

    // world.system<PollRate, Link>("registration")
    //     .kind(flecs::OnStart)
    //     .each([](flecs::entity e, DeviceCapability& dcap) {
    //         auto link = e.target(Link)
    //         auto resp = trust::HttpsClient::getInstance().Get(dcap.href);
    //     });

    world.system<PollRate>("update_dcap")
        .each([](flecs::entity e, PollRate& poll){
            poll.seconds--;
            if (poll.seconds == 0){
                auto resp = trust::HttpsClient::getInstance().Get("/dcap");
                std::cout << resp << std::endl;
                poll.seconds = 5;
            }
        });
} 
    
} // namespace dcap
} // namespace sep
