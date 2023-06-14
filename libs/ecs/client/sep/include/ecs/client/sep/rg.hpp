#ifndef __ECS_CLIENT_RG_H__
#define __ECS_CLIENT_RG_H__

#include <flecs.h>
#include <sep/models/registration.hpp>
#include <string>

namespace ecs {
namespace client {
namespace rg {

struct Module {
  Module(flecs::world &world);
};

} // namespace rg
} // namespace client
} // namespace ecs
#endif // __ECS_CLIENT_RG_H__