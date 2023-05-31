#include <ecs/server/sep/sdev.hpp>
#include <sep/xml/utilities.hpp>

using namespace gsp::sdev;

Module::Module(flecs::world &world) {
  world.module<Module>();
  world.component<sep::SelfDevice>();
};