#ifndef __GSP_ECS_DCAP_H__
#define __GSP_ECS_DCAP_H__

#include <flecs.h>

namespace ecs {
namespace server {
namespace dcap {

///
/// this module establishes the DeviceCapability as a component within the ECS
/// world
///
struct Module {
  Module(flecs::world &world);
};

} // namespace dcap
} // namespace server
} // namespace ecs
#endif // __GSP_ECS_DCAP_H__
