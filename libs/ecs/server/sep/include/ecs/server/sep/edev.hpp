#ifndef __GSP_ECS_EDEV_H__
#define __GSP_ECS_EDEV_H__

#include <flecs.h>
#include <sep/models/end_device.hpp>

namespace gsp {
namespace edev {
std::string generateURI(const sep::EndDevice &edev);
struct Module {
  Module(flecs::world &world);
};

} // namespace edev
} // namespace gsp
#endif // __GSP_ECS_EDEV_H__