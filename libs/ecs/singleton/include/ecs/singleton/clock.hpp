#ifndef __ECS_SINGLETON_H__
#define __ECS_SINGLETON_H__

#include <cstdint>
#include <flecs.h>

namespace ecs {
namespace singleton {

struct Clock {
  uint64_t time;
  int16_t offset;
};

struct Module {
  Module(flecs::world &world);
};

} // namespace singleton
} // namespace ecs
#endif // __ECS_SINGLETON_H__