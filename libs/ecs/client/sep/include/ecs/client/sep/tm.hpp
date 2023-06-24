#ifndef __ECS_CLIENT_TM_H__
#define __ECS_CLIENT_TM_H__

#include <cstdint>
#include <flecs.h>
#include <sep/models/time.hpp>
#include <stdint.h>
#include <string>

namespace ecs {
namespace client {
namespace tm {

struct Clock {
  uint64_t time;
  int16_t offset;
};

struct Module {
  Module(flecs::world &world);
};

} // namespace tm
} // namespace client
} // namespace ecs
#endif // __ECS_CLIENT_TM_H__