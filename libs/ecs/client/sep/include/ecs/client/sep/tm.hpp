#ifndef __ECS_CLIENT_TM_H__
#define __ECS_CLIENT_TM_H__

#include <flecs.h>
#include <sep/models/time.hpp>

namespace ecs {
namespace client {
namespace tm {

///
/// this module establishes the Time resource as a component within the ECS
/// world
///
struct Module {
  Module(flecs::world &world);
};

} // namespace tm
} // namespace client
} // namespace ecs
#endif // __ECS_CLIENT_TM_H__
