#include <ecs/server/sep/dcap.hpp>

using namespace gsp::dcap;

Module::Module(flecs::world &world) {
  world.module<Module>();
  world.component<sep::DeviceCapability>();
};