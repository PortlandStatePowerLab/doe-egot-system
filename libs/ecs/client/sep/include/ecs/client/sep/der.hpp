#ifndef __ECS_CLIENT_DER_H__
#define __ECS_CLIENT_DER_H__

#include <flecs.h>
#include <sep/models/der.hpp>

namespace ecs {
namespace client {
namespace der {

///
/// This module sets the startup system for all IEEE 2030.5 resources by
/// requesting the DER and updating the links it contains. It also
/// establishes observers to make requests when the links are modified to keep
/// other modules updated.
///
struct Module {
  Module(flecs::world &world);

  ///
  /// request the DER resource from an IEEE 2030.5 Server
  ///
  static void getDERCapabilities(flecs::entity e, sep::DERCapabilityLink &link);
  static void getDERSettings(flecs::entity e, sep::DERSettingsLink &link);
  static void getDERStatus(flecs::entity e, sep::DERStatusLink &link);
  static void getDERAvailablity(flecs::entity e,
                                sep::DERAvailabilityLink &link);

  ///
  /// update the DER resource and all its links
  ///
  static void updateDER(flecs::entity e, sep::DERList &der);
};
} // namespace der
} // namespace client
} // namespace ecs
#endif // __ECS_CLIENT_DER_H__
