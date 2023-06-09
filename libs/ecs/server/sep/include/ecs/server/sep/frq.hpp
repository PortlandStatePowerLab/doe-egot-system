#ifndef __GSP_ECS_FRQ_H__
#define __GSP_ECS_FRQ_H__

#include <flecs.h>
#include <sep/models/flow_reservation_request.hpp>
#include <sep/models/flow_reservation_response.hpp>
namespace gsp {
namespace frq {
std::string generateURI(const sep::FlowReservationRequest &frq);
sep::FlowReservationResponse
generateResponse(const sep::FlowReservationRequest &frq);
struct Module {
  Module(flecs::world &world);
};

} // namespace frq
} // namespace gsp
#endif // __GSP_ECS_FRQ_H__