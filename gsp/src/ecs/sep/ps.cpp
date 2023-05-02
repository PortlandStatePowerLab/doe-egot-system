#include "include/sep/ps.hpp"

namespace ps {
Module::Module(flecs::world &world) {
  world.module<Module>();
  world.component<sep::PowerStatus>();
};
} // namespace ps