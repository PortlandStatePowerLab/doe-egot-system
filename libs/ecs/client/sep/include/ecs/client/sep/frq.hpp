#ifndef __ECS_CLIENT_FRQ_H__
#define __ECS_CLIENT_FRQ_H__

#include <flecs.h>
#include <sep/models/flow_reservation_request.hpp>
#include <string>

namespace ecs {
namespace client {
namespace frq {

struct Module {
  Module(flecs::world &world);
};

} // namespace frq
} // namespace client
} // namespace ecs
#endif // __ECS_CLIENT_FRQ_H__