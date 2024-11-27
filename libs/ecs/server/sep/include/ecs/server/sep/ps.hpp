#ifndef __GSP_ECS_PS_H__
#define __GSP_ECS_PS_H__

#include <flecs.h>
#include <sep/models/power_status.hpp>

namespace ecs {
namespace server {
namespace ps {

///
/// this module establishes the PowerStatus resource as a component within the
/// ECS world
///
struct Module {
  Module(flecs::world &world);
};

} // namespace ps
} // namespace server
} // namespace ecs
#endif // __GSP_ECS_PS_H__
