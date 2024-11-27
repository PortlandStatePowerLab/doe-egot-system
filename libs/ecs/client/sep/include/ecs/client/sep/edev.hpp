#ifndef __ECS_CLIENT_EDEV_H__
#define __ECS_CLIENT_EDEV_H__

#include <flecs.h>
#include <sep/models/end_device.hpp>
#include <sep/models/flow_reservation_response.hpp>

namespace ecs {
namespace client {
namespace edev {

///
/// this module establishes the EndDevice as a component within the ECS world
///
struct Module {
  Module(flecs::world &world);

  ///
  /// request the Registration resource from a IEEE 2030.5 Server
  ///
  static void getRegistration(flecs::entity e, sep::RegistrationLink &link);

  ///
  /// request the DERList resource from a IEEE 2030.5 Server
  ///
  static void getDERListLink(flecs::entity e, sep::DERListLink &link);

  ///
  /// request the FlowReservationResponseList from a IEEE 2030.5 Server
  ///
  static void getFRPListLink(flecs::entity e,
                             sep::FlowReservationResponseListLink &link);
};

} // namespace edev
} // namespace client
} // namespace ecs
#endif // __ECS_CLIENT_EDEV_H__
