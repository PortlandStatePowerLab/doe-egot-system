#ifndef __ECS_CLIENT_PS_H__
#define __ECS_CLIENT_PS_H__

#include <flecs.h>
#include <sep/models/power_status.hpp>

namespace ecs {
namespace client {
namespace ps {

///
/// this module establishes the PowerStatus resource as a component within the
/// ECS world
///
struct Module {
  Module(flecs::world &world);
};

} // namespace ps
} // namespace client
} // namespace ecs
#endif // __ECS_CLIENT_PS_H__
