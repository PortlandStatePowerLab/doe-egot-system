#include <ecs/client/sep/dcap.hpp>
#include <ecs/client/sep/edev.hpp>
#include <ecs/client/sep/rg.hpp>
#include <ecs/client/sep/tm.hpp>
#include <iostream>
#include <sep/xml/device_capability_adapter.hpp>
#include <sep/xml/end_device_adapter.hpp>
#include <sep/xml/self_device_adapter.hpp>
#include <sep/xml/time_adapter.hpp>
#include <trust/https/client.hpp>
#include <utilities/utilities.hpp>

ecs::client::dcap::Module::Module(flecs::world &world) {
  world.module<Module>();

  world.component<sep::DeviceCapabilityLink>();
  world.component<sep::EndDeviceListLink>();
  world.component<sep::SelfDeviceLink>();
  world.component<sep::TimeLink>();

  world.system<sep::DeviceCapabilityLink>("startup")
      .kind(flecs::OnStart)
      .each([](flecs::entity e, sep::DeviceCapabilityLink &link) {
        std::cout << "Running DeviceCapabilities" << std::endl;
        auto resp = trust::HttpsClient::getInstance().Get(link.href);
        std::cout << resp << std::endl;

        if (resp.result_int() == 200) {
          std::string msg = boost::beast::buffers_to_string(resp.body().data());
          sep::DeviceCapability dcap;
          xml::Parse(msg, &dcap);
          e.world().entity().set<sep::DeviceCapability>(dcap);
          if (dcap.end_device_list_link.has_value()) {
            e.set<sep::EndDeviceListLink>(dcap.end_device_list_link.value());
          }
          if (dcap.self_device_link.has_value()) {
            e.set<sep::SelfDeviceLink>(dcap.self_device_link.value());
          }
          if (dcap.time_link.has_value()) {
            e.set<sep::TimeLink>(dcap.time_link.value());
          }
        }
      });

  world.system<sep::DeviceCapability>("dcaplink")
      .each([](flecs::entity e, sep::DeviceCapability &dcap) {
        std::cout << psu::utilities::getTime() << " : "
                  << psu::utilities::getTime() % dcap.poll_rate << std::endl;
        if (psu::utilities::getTime() % dcap.poll_rate == 0) {
          std::cout << "Polling DeviceCapabilities ..." << std::endl;
          auto resp = trust::HttpsClient::getInstance().Get(dcap.href);
          std::cout << resp << std::endl;

          std::string msg = boost::beast::buffers_to_string(resp.body().data());
          xml::Parse(msg, &dcap);
          if (dcap.end_device_list_link.has_value()) {
            e.set<sep::EndDeviceListLink>(dcap.end_device_list_link.value());
          }
          if (dcap.self_device_link.has_value()) {
            e.set<sep::SelfDeviceLink>(dcap.self_device_link.value());
          }
          if (dcap.time_link.has_value()) {
            e.set<sep::TimeLink>(dcap.time_link.value());
          }
        }
      });

  world.observer<sep::SelfDeviceLink>("sdevlink")
      .event(flecs::OnSet)
      .each([](flecs::entity e, sep::SelfDeviceLink &link) {
        std::cout << "Event SelfDevice" << std::endl;
        auto resp = trust::HttpsClient::getInstance().Get(link.href);
        std::cout << resp << std::endl;
        if (resp.result_int() == 200) {
          std::string msg = boost::beast::buffers_to_string(resp.body().data());
          sep::SelfDevice sdev;
          xml::Parse(msg, &sdev);
          e.world().entity().set<sep::SelfDevice>(sdev);
        }
      });

  world.observer<sep::EndDeviceListLink>("edevlist")
      .event(flecs::OnSet)
      .each([](flecs::entity e, sep::EndDeviceListLink &list_link) {
        std::cout << "Event EndDeviceList" << std::endl;
        auto resp = trust::HttpsClient::getInstance().Get(list_link.href);
        std::cout << resp << std::endl;
        if (resp.result_int() == 200) {
          std::string msg = boost::beast::buffers_to_string(resp.body().data());
          sep::EndDeviceList list;
          xml::Parse(msg, &list);
          for (auto &edev : list.end_devices) {
            std::cout << (edev.lfdi ==
                          trust::HttpsClient::getInstance().getLFDI())
                      << std::endl;
            if (edev.lfdi == trust::HttpsClient::getInstance().getLFDI()) {
              e.world().entity().set<sep::EndDevice>(edev);
            }
          }
        }
      });

  world.observer<sep::TimeLink>("timelink")
      .event(flecs::OnSet)
      .each([](flecs::entity e, sep::TimeLink &link) {
        std::cout << "Event Time" << std::endl;
        auto resp = trust::HttpsClient::getInstance().Get(link.href);
        std::cout << resp << std::endl;
        if (resp.result_int() == 200) {
          std::string msg = boost::beast::buffers_to_string(resp.body().data());
          sep::Time tm;
          xml::Parse(msg, &tm);
          e.world().entity().set<sep::Time>(tm);
        }
      });
};