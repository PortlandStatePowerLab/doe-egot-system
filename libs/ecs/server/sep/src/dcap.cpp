#include <ecs/server/sep/dcap.hpp>
#include <sep/models/device_capability.hpp>

namespace ecs {
namespace server {
namespace dcap {
Module::Module(flecs::world &world) {
  world.module<Module>();
  world.component<sep::DeviceCapability>();
};
} // namespace dcap
} // namespace server
} // namespace ecs
