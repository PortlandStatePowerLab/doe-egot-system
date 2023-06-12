#include <ecs/client/sep/dcap.hpp>
#include <iostream>
#include <sep/xml/device_capability_adapter.hpp>
#include <trust/https/client.hpp>

ecs::client::dcap::Module::Module(flecs::world &world) {
  world.module<Module>();

  world.component<sep::DeviceCapabilityLink>();
  world.component<sep::EndDeviceListLink>();
  world.component<sep::SelfDeviceLink>();
  world.component<sep::TimeLink>();

  world.system<sep::DeviceCapabilityLink>("capabilities")
      .kind(flecs::OnStart)
      .each([](flecs::entity e, sep::DeviceCapabilityLink &link) {
        std::cout << "Running DeviceCapabilities" << std::endl;
        auto resp = trust::HttpsClient::getInstance().Get(link.href);
        std::cout << resp << std::endl;

        std::string msg = boost::beast::buffers_to_string(resp.body().data());
        sep::DeviceCapability dcap;
        xml::Parse(msg, &dcap);
        if (dcap.end_device_list_link.is_initialized()) {
          e.set<sep::EndDeviceListLink>(dcap.end_device_list_link.value());
        }
        if (dcap.self_device_link.is_initialized()) {
          e.set<sep::SelfDeviceLink>(dcap.self_device_link.value());
        }
        if (dcap.time_link.is_initialized()) {
          e.set<sep::TimeLink>(dcap.time_link.value());
        }
      });

  world.observer<sep::SelfDeviceLink>("selfdev")
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