#include <ecs/client/sep/frp.hpp>
#include <sep/models/flow_reservation_request.hpp>
#include <sep/xml/flow_reservation_request_adapter.hpp>
#include <sep/xml/flow_reservation_response_adapter.hpp>
#include <trust/https/client.hpp>
#include <utilities/utilities.hpp>

ecs::client::frp::Module::Module(flecs::world &world) {
  world.module<Module>();

  world.component<sep::FlowReservationResponse>();
  world.component<sep::FlowReservationResponseList>();
  world.component<sep::FlowReservationResponseListLink>();

  world.observer<sep::FlowReservationResponseListLink>("frplist")
      .event(flecs::OnSet)
      .each(
          [](flecs::entity e, sep::FlowReservationResponseListLink &list_link) {
            std::cout << "Event FlowReservationResponseListLink" << std::endl;
          });
};
