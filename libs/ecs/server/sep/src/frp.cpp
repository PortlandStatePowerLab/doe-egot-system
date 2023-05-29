#include <ecs/server/sep/frp.hpp>

using namespace gsp::frp;

Module::Module(flecs::world &world) {
  world.module<Module>();
  world.component<sep::FlowReservationResponse>();
};
