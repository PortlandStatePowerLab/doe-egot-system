#ifndef __ECS_CLIENT_EDEV_H__
#define __ECS_CLIENT_EDEV_H__

#include <flecs.h>
#include <sep/models/end_device.hpp>

namespace ecs {
namespace client {
namespace edev {

///
/// this module establishes the EndDevice as a component within the ECS world
///
struct Module {
  Module(flecs::world &world);
};

} // namespace edev
} // namespace client
} // namespace ecs
#endif // __ECS_CLIENT_EDEV_H__
