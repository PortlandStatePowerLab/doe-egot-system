#include <ecs/server/sep/frp.hpp>
#include <sep/models/flow_reservation_response.hpp>

namespace ecs {
namespace server {
namespace frp {
Module::Module(flecs::world &world) {
  world.module<Module>();
  world.component<sep::FlowReservationResponse>();
};
} // namespace frp
} // namespace server
} // namespace ecs
