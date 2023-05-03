#ifndef __GSP_ECS_TIME_H__
#define __GSP_ECS_TIME_H__

#include <flecs.h>
#include <ieee-2030.5/time.hpp>

namespace gsp {
namespace time {

struct Module {
  Module(flecs::world &world);
};

} // namespace time
} // namespace gsp
#endif // __GSP_ECS_TIME_H__