#ifndef __GSP_ECS_EDEV_H__
#define __GSP_ECS_EDEV_H__

#include <flecs.h>
#include <sep/models/end_device.hpp>

namespace ecs {
namespace server {
namespace edev {

///
/// convert the ECS path to URI for client requests
///
std::string generateURI(const sep::EndDevice &edev);

///
/// This module sets the EndDevice resources as a component within the ECS
///
/// Note: eventually there may be a system that is required to check for updates
/// to EndDevices that need to be propogated throughout the rest of the server
///
struct Module {
  Module(flecs::world &world);
};

} // namespace edev
} // namespace server
} // namespace ecs
#endif // __GSP_ECS_EDEV_H__
