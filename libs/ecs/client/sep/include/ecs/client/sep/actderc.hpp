#ifndef __ECS_CLIENT_ACTDERC_H__
#define __ECS_CLIENT_ACTDERC_H__

#include <flecs.h>
#include <sep/models/der_control.hpp>

namespace ecs {
namespace client {
namespace actderc {

///
/// This module sets the startup system for all IEEE 2030.5 resources by
/// requesting the DeviceCapability and updating the links it contains. It also
/// establishes observers to make requests when the links are modified to keep
/// other modules updated.
///
struct Module {
  Module(flecs::world &world);

  ///
  /// request the DeviceCapability resource from an IEEE 2030.5 Server
  ///
  static void getDeviceCapability(flecs::entity e,
                                  sep::DERControlLink &link);
  ///
  /// update the DeviceCapability resource and all its links
  ///
  static void updateDeviceCapability(flecs::entity e,
                                     sep::DERControl &dcap);
};
} // namespace dcap
} // namespace client
} // namespace ecs
#endif // __ECS_CLIENT_ACTDERC_H__