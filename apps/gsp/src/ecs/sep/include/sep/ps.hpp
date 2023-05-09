#ifndef __GSP_ECS_PS_H__
#define __GSP_ECS_PS_H__

#include <flecs.h>
#include <ieee-2030.5/power_status.hpp>

namespace gsp {
namespace ps {

struct Module {
  Module(flecs::world &world);
};

} // namespace ps
} // namespace gsp
#endif // __GSP_ECS_PS_H__