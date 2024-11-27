#ifndef __ECS_CLIENT_RG_H__
#define __ECS_CLIENT_RG_H__

#include <flecs.h>
#include <sep/models/registration.hpp>

namespace ecs {
namespace client {
namespace rg {

///
/// this module establishes the Registration resources as a component within the
/// ECS world
///
struct Module {
  Module(flecs::world &world);
};

} // namespace rg
} // namespace client
} // namespace ecs
#endif // __ECS_CLIENT_RG_H__
