#ifndef __GSP_ECS_FRP_H__
#define __GSP_ECS_FRP_H__

#include <flecs.h>
#include <sep/models/flow_reservation_response.hpp>

namespace gsp {
namespace frp {

struct Module {
  Module(flecs::world &world);
};

} // namespace frp
} // namespace gsp
#endif // __GSP_ECS_FRP_H__