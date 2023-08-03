#include <ecs/client/sep/frq.hpp>
#include <iostream>
#include <sep/xml/flow_reservation_request_adapter.hpp>
#include <sep/xml/flow_reservation_response_adapter.hpp>
#include <trust/https/client.hpp>
#include <utilities/utilities.hpp>

ecs::client::frq::Module::Module(flecs::world &world) {
  world.module<Module>();

  world.component<sep::FlowReservationRequest>();
  world.component<sep::FlowReservationResponseList>();
  world.component<sep::FlowReservationResponseListLink>();
};