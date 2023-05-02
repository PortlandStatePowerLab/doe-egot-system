#include "include/sep/frq.hpp"

namespace frq {
Module::Module(flecs::world &world) {
  world.module<Module>();
  world.component<sep::FlowReservationRequest>();
};
} // namespace frq