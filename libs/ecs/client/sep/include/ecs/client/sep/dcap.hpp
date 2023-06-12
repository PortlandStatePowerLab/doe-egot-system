#ifndef __ECS_CLIENT_DCAP_H__
#define __ECS_CLIENT_DCAP_H__

#include <flecs.h>
#include <sep/models/device_capability.hpp>
#include <string>

namespace ecs {
namespace client {
namespace dcap {

struct Module {
  Module(flecs::world &world);
};

} // namespace dcap
} // namespace client
} // namespace ecs
#endif // __ECS_CLIENT_DCAP_H__