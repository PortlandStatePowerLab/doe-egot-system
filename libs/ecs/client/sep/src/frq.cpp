#include <ecs/client/sep/frq.hpp>
#include <iostream>
#include <sep/models/flow_reservation_request.hpp>
#include <sep/xml/flow_reservation_request_adapter.hpp>
#include <sep/xml/flow_reservation_response_adapter.hpp>
#include <trust/https/client.hpp>
#include <utilities/utilities.hpp>

ecs::client::frq::Module::Module(flecs::world &world) {
  world.module<Module>();

  world.component<sep::FlowReservationRequest>();
  world.component<sep::FlowReservationResponseList>();
  world.component<sep::FlowReservationResponseListLink>();

  world.observer<sep::FlowReservationRequest>("post-frq")
      .event(flecs::OnSet)
      .each([](flecs::entity e, sep::FlowReservationRequest &frq) {
        std::cout << "Event FRQ:" << std::endl;

        auto f = e.world()
                     .filter_builder<sep::FlowReservationResponseListLink>()
                     .build();

        f.each([frq](flecs::entity e,
                     sep::FlowReservationResponseListLink &list_link) {
          auto resp = trust::HttpsClient::getInstance().Post(
              list_link.href, xml::Serialize(frq));

          std::cout << resp << std::endl;
        });
      });
};
