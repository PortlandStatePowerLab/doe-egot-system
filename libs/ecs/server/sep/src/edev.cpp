#include <ecs/server/sep/edev.hpp>
#include <sep/xml/utilities.hpp>
#include <utilities/utilities.hpp>

using namespace gsp::edev;

Module::Module(flecs::world &world) {
  world.module<Module>();
  world.component<sep::EndDevice>();
};