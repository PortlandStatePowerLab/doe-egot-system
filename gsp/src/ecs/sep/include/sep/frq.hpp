#ifndef __GSP_ECS_FRQ_H__
#define __GSP_ECS_FRQ_H__

#include <flecs.h>
#include <ieee-2030.5/flow_reservation_request.hpp>

namespace gsp {
namespace frq {

struct Module {
  Module(flecs::world &world);
};

} // namespace frq
} // namespace gsp
#endif // __GSP_ECS_FRQ_H__