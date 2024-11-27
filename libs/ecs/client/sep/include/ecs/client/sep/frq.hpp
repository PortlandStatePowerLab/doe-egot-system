#ifndef __ECS_CLIENT_FRQ_H__
#define __ECS_CLIENT_FRQ_H__

#include <flecs.h>
#include <sep/models/flow_reservation_request.hpp>

namespace ecs {
namespace client {
namespace frq {

///
/// this module establishes the FlowReservationRequest as a component within the
/// ECS world
///
struct Module {
  Module(flecs::world &world);

  ///
  /// post a FlowReservationRequest to an IEEE 2030.5 server
  ///
};

} // namespace frq
} // namespace client
} // namespace ecs
#endif // __ECS_CLIENT_FRQ_H__
