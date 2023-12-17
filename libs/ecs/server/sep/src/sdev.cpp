#include <ecs/server/sep/sdev.hpp>
#include <sep/models/self_device.hpp>

namespace ecs {
namespace server {
namespace sdev {
Module::Module(flecs::world &world) {
  world.module<Module>();
  world.component<sep::SelfDevice>();
};
} // namespace sdev
} // namespace server
} // namespace ecs
