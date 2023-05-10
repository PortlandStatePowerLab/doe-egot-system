#include <ecs/server/sep/frq.hpp>

using namespace gsp::frq;

Module::Module(flecs::world &world) {
  world.module<Module>();
  world.component<sep::FlowReservationRequest>();
};