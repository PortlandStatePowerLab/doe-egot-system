#ifndef __ECS_CLIENT_DERA_H__
#define __ECS_CLIENT_DERA_H__

#include <flecs.h>
#include <sep/models/der_availability.hpp>

namespace ecs {
namespace client {
namespace dera {

///
/// This module sets the startup system for all IEEE 2030.5 resources by
/// requesting the DERAvailability and updating the links it contains. It also
/// establishes observers to make requests when the links are modified to keep
/// other modules updated.
///
struct Module {
  Module(flecs::world &world);

  ///
  /// request the DERAvailability resource from an IEEE 2030.5 Server
  ///
  static void getDERAvailability(flecs::entity e,
                                  sep::DERAvailabilityLink &link);
  ///
  /// update the DERAvailability resource and all its links
  ///
  static void updateDERAvailability(flecs::entity e,
                                     sep::DERAvailability &dderc);
};
} // namespace dcap
} // namespace client
} // namespace ecs
#endif // __ECS_CLIENT_DERA_H__