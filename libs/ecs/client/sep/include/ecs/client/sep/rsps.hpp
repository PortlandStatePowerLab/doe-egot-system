#ifndef __ECS_CLIENT_RSPS_H__
#define __ECS_CLIENT_RSPS_H__

#include <flecs.h>
#include <sep/models/response_set.hpp>

namespace ecs {
namespace client {
namespace rsps {

///
/// this module establishes the ResponseSet as a component within the ECS world
///
struct Module {
  Module(flecs::world &world);
};

} // namespace rsps
} // namespace client
} // namespace ecs
#endif // __ECS_CLIENT_RSPS_H__
