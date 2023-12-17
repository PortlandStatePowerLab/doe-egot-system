#ifndef __GSP_ECS_FRP_H__
#define __GSP_ECS_FRP_H__

#include <flecs.h>

namespace ecs {
namespace server {
namespace frp {

///
/// This module establishes the FlowReservationResponse as a component withint
/// he ECS world
///
struct Module {
  Module(flecs::world &world);
};

} // namespace frp
} // namespace server
} // namespace ecs
#endif // __GSP_ECS_FRP_H__
