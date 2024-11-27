#include <ecs/server/sep/ps.hpp>

namespace ecs {
namespace server {
namespace ps {
Module::Module(flecs::world &world) {
  world.module<Module>();
  world.component<sep::PowerStatus>();
};
} // namespace ps
} // namespace server
} // namespace ecs
