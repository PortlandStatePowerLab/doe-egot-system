#include "include/sep/rsp.hpp"

using namespace gsp::rsp;

Module::Module(flecs::world &world) {
  world.module<Module>();
  world.component<sep::Response>();
};