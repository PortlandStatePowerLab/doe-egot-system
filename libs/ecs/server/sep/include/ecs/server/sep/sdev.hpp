#ifndef __GSP_ECS_SDEV_H__
#define __GSP_ECS_SDEV_H__

#include <flecs.h>

namespace ecs {
namespace server {
namespace sdev {

///
/// This module establishes the SelfDevice as a component within the ECS world
///
struct Module {
  Module(flecs::world &world);
};

} // namespace sdev
} // namespace server
} // namespace ecs
#endif // __GSP_ECS_SDEV_H__
