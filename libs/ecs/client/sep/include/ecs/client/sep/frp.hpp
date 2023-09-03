#ifndef __ECS_CLIENT_FRP_H__
#define __ECS_CLIENT_FRP_H__

#include <flecs.h>
#include <sep/models/flow_reservation_response.hpp>
#include <sep/models/flow_reservation_response_response.hpp>
#include <string>

namespace ecs {
namespace client {
namespace frp {

struct Module {
  Module(flecs::world &world);
};

} // namespace frp
} // namespace client
} // namespace ecs
#endif // __ECS_CLIENT_FRP_H__