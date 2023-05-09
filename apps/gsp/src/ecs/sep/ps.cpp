#include "include/sep/ps.hpp"

using namespace gsp::ps;

Module::Module(flecs::world &world) {
  world.module<Module>();
  world.component<sep::PowerStatus>();
};
