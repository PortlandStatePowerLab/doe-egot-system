#include <ecs/client/sep/fsa.hpp>

namespace ecs {
namespace client {
namespace fsab {

Module::Module(flecs::world &world) { world.module<Module>(); };

} // namespace fsab
} // namespace client
} // namespace ecs
