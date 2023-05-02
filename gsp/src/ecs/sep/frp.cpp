#include "include/sep/frp.hpp"
#include "ieee-2030.5/flow_reservation_response.hpp"

namespace frp {
Module::Module(flecs::world &world) {
  world.module<Module>();
  world.component<sep::FlowReservationResponse>();
};
} // namespace frp