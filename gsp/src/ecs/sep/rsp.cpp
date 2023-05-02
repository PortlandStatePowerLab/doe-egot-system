#include "include/sep/rsp.hpp"

namespace rsp {
Module::Module(flecs::world &world) {
  world.module<Module>();
  world.component<sep::Response>();
};
} // namespace rsp