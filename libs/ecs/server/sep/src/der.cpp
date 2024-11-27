#include <ecs/server/sep/der.hpp>
#include <sep/models/der.hpp>
#include <sep/models/der_availability.hpp>
#include <sep/models/der_capability.hpp>
#include <sep/models/der_settings.hpp>
#include <sep/models/der_status.hpp>
namespace ecs {
namespace server {
namespace der {

Module::Module(flecs::world &world) {
  world.module<Module>();
  world.component<sep::DER>();
  world.component<sep::DERList>();
  world.component<sep::DERCapability>();
  world.component<sep::DERSettings>();
  world.component<sep::DERStatus>();
  world.component<sep::DERAvailability>();
};
} // namespace der
} // namespace server
} // namespace ecs
