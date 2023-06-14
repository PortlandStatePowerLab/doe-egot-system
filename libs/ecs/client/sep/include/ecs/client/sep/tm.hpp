#ifndef __ECS_CLIENT_TM_H__
#define __ECS_CLIENT_TM_H__

#include <flecs.h>
#include <sep/models/time.hpp>
#include <string>

namespace ecs {
namespace client {
namespace tm {

struct Module {
  Module(flecs::world &world);
};

} // namespace tm
} // namespace client
} // namespace ecs
#endif // __ECS_CLIENT_TM_H__