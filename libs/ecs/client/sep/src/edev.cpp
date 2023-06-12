#include <ecs/client/sep/edev.hpp>
#include <iostream>
#include <sep/xml/device_capability_adapter.hpp>
#include <trust/https/client.hpp>

ecs::client::edev::Module::Module(flecs::world &world) {
  world.module<Module>();

  world.component<sep::DeviceCapabilityLink>();
  world.component<sep::EndDeviceListLink>();
  world.component<sep::SelfDeviceLink>();
  world.component<sep::TimeLink>();

  world.observer<sep::SelfDeviceLink>("self dev")
      .event(flecs::OnSet)
      .each([](flecs::entity e, sep::SelfDeviceLink &link) {
        std::cout << "Running SelfDevice" << std::endl;
        auto resp = trust::HttpsClient::getInstance().Get(link.href);
        std::cout << resp << std::endl;
      });

  world.observer<sep::EndDeviceListLink>("edevlist")
      .event(flecs::OnSet)
      .each([](flecs::entity e, sep::EndDeviceListLink &list_link) {
        std::cout << "Running EndDevice List" << std::endl;
        auto resp = trust::HttpsClient::getInstance().Get(list_link.href);
        std::cout << resp << std::endl;
      });

  world.observer<sep::TimeLink>("timesync")
      .event(flecs::OnSet)
      .each([](flecs::entity e, sep::TimeLink &link) {
        std::cout << "Running Time" << std::endl;
        auto resp = trust::HttpsClient::getInstance().Get(link.href);
        std::cout << resp << std::endl;
      });
};