#ifndef __ECS_CLIENT_DCAP_H__
#define __ECS_CLIENT_DCAP_H__

#include <flecs.h>
#include <sep/models/device_capability.hpp>

namespace ecs {
namespace client {
namespace dcap {

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
                                  sep::DeviceCapabilityLink &link);
  ///
  /// update the DeviceCapability resource and all its links
  ///
  static void updateDeviceCapability(flecs::entity e,
                                     sep::DeviceCapability &dcap);

  ///
  /// request the SelfDevice from an IEEE 2030.5 Server
  ///
  static void getSelfDevice(flecs::entity e, sep::SelfDeviceLink &link);

  ///
  /// request the EndDeviceList from an IEEE 2030.5 Server
  ///
  static void getEndDevice(flecs::entity e, sep::EndDeviceListLink &list_link);

  ///
  /// request the Time from an IEEE 2030.5 Server
  ///
  static void getTime(flecs::entity e, sep::TimeLink &link);
};
} // namespace dcap
} // namespace client
} // namespace ecs
#endif // __ECS_CLIENT_DCAP_H__
