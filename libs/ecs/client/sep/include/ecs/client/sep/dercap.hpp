#ifndef __ECS_CLIENT_DERCAP_H__
#define __ECS_CLIENT_DERCAP_H__

#include <flecs.h>
#include <sep/models/der_capability.hpp>

namespace ecs {
namespace client {
namespace derc {

///
/// This module sets the startup system for all IEEE 2030.5 resources by
/// requesting the DERControl and updating the links it contains. It also
/// establishes observers to make requests when the links are modified to keep
/// other modules updated.
///
struct Module {
  Module(flecs::world &world);

  ///
  /// request the DERControl resource from an IEEE 2030.5 Server
  ///
  static void getDERCapability(flecs::entity e,
                                  sep::DERCapabilityLink &link);
  ///
  /// update the DERControl resource and all its links
  ///
  static void updateDERCapability(flecs::entity e,
                                     sep::DERCapability &derc);
};
} // namespace dcap
} // namespace client
} // namespace ecs
#endif // __ECS_CLIENT_DERCAP_H__