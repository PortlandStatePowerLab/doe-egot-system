#ifndef __GSP_ECS_SDEV_H__
#define __GSP_ECS_SDEV_H__

#include <flecs.h>
#include <sep/models/self_device.hpp>

namespace gsp {
namespace sdev {

struct Module {
  Module(flecs::world &world);
};

} // namespace sdev
} // namespace gsp
#endif // __GSP_ECS_SDEV_H__