#ifndef __ECS_SINGLETON_H__
#define __ECS_SINGLETON_H__

#include <cstdint>
#include <flecs.h>

namespace ecs {
namespace singleton {

struct Clock {
  int64_t utc;
  int64_t local;
  int64_t offset;
};

void generateClock(flecs::world &world);

struct Module {
  Module(flecs::world &world);
};

} // namespace singleton
} // namespace ecs
#endif // __ECS_SINGLETON_H__