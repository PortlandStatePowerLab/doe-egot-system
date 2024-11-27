#ifndef __GSP_ECS_FRQ_H__
#define __GSP_ECS_FRQ_H__

#include <flecs.h>
#include <sep/models/flow_reservation_request.hpp>
#include <sep/models/flow_reservation_response.hpp>
namespace ecs {
namespace server {
namespace frq {
///
/// map ECS path for HTTPS client requests
///
std::string generateURI(const sep::FlowReservationRequest &frq);

///
/// create FlowReservationResponse for FlowReservationRequest recieved from
/// client
///
sep::FlowReservationResponse
generateResponse(const sep::FlowReservationRequest &frq);

///
/// this module establishes the FlowReservationRequest resource as a
/// component within the ECS world
///
struct Module {
  Module(flecs::world &world);
};

} // namespace frq
} // namespace server
} // namespace ecs
#endif // __GSP_ECS_FRQ_H__
