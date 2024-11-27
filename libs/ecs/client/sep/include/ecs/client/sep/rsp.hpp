#ifndef __ECS_CLIENT_RSP_H__
#define __ECS_CLIENT_RSP_H__

#include <flecs.h>
#include <sep/models/response.hpp>

namespace ecs {
namespace client {
namespace rsp {

///
/// this module establishes the Response as a component within the ECS world
///
struct Module {
  Module(flecs::world &world);
};

} // namespace rsp
} // namespace client
} // namespace ecs
#endif // __ECS_CLIENT_RSP_H__
