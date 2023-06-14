#include "sep/models/flow_reservation_request.hpp"
#include "sep/models/flow_reservation_response.hpp"
#include "sep/models/registration.hpp"
#include <ecs/client/sep/edev.hpp>
#include <ecs/client/sep/rg.hpp>
#include <iostream>
#include <sep/models/end_device.hpp>
#include <sep/xml/registration_adapter.hpp>
#include <trust/https/client.hpp>

ecs::client::edev::Module::Module(flecs::world &world) {
  world.module<Module>();

  world.component<sep::EndDevice>();
  world.component<sep::RegistrationLink>();
  world.component<sep::FlowReservationRequestListLink>();
  world.component<sep::FlowReservationResponseListLink>();

  world.observer<sep::EndDevice>("enddevice")
      .event(flecs::OnSet)
      .each([](flecs::entity e, sep::EndDevice &edev) {
        std::cout << "Event EndDevice" << std::endl;
        if (edev.registration_link.has_value()) {
          e.set<sep::RegistrationLink>(edev.registration_link.value());
        }
        if (edev.flow_reservation_request_list_link.has_value()) {
          e.set<sep::FlowReservationRequestListLink>(
              edev.flow_reservation_request_list_link.value());
        }
        if (edev.flow_reservation_response_list_link.has_value()) {
          e.set<sep::FlowReservationResponseListLink>(
              edev.flow_reservation_response_list_link.value());
        }
      });

  world.observer<sep::RegistrationLink>("rglink")
      .event(flecs::OnSet)
      .each([](flecs::entity e, sep::RegistrationLink &link) {
        std::cout << "Event FlowReservationRequestListLink" << std::endl;
        auto resp = trust::HttpsClient::getInstance().Get(link.href);
        std::cout << resp << std::endl;
        if (resp.result_int() == 200) {
          std::string msg = boost::beast::buffers_to_string(resp.body().data());
          sep::Registration rg;
          xml::Parse(msg, &rg);
          e.world().entity().set<sep::Registration>(rg);
        }
      });

  world.system<sep::FlowReservationRequestListLink>("frqlist").each(
      [](flecs::entity e, sep::FlowReservationRequestListLink &list_link) {
        std::cout << "Event FlowReservationRequestListLink" << std::endl;
      });

  world.observer<sep::FlowReservationResponseListLink>("frplist")
      .event(flecs::OnSet)
      .each(
          [](flecs::entity e, sep::FlowReservationResponseListLink &list_link) {
            std::cout << "Event FlowReservationResponseListLink" << std::endl;
          });
};