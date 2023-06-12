#ifndef __ECS_CLIENT_EDEV_H__
#define __ECS_CLIENT_EDEV_H__

#include <flecs.h>
#include <sep/models/end_device.hpp>
#include <string>

namespace ecs {
namespace client {
namespace edev {

struct Module {
  Module(flecs::world &world);
};

} // namespace edev
} // namespace client
} // namespace ecs
#endif // __ECS_CLIENT_EDEV_H__