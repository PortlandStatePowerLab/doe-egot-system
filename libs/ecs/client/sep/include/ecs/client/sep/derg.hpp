#ifndef __ECS_CLIENT_DERG_H__
#define __ECS_CLIENT_DERG_H__

#include <flecs.h>
#include <sep/models/der_settings.hpp>

namespace ecs {
namespace client {
namespace derc {

///
/// This module sets the startup system for all IEEE 2030.5 resources by
/// requesting the DERSettings and updating the links it contains. It also
/// establishes observers to make requests when the links are modified to keep
/// other modules updated.
///
struct Module {
  Module(flecs::world &world);

  ///
  /// request the DERSettings resource from an IEEE 2030.5 Server
  ///
  static void getDERSettings(flecs::entity e,
                                  sep::DERSettingsLink &link);
  ///
  /// update the DERSettings resource and all its links
  ///
  static void updateDERSettings(flecs::entity e,
                                     sep::DERSettings &derg);
};
} // namespace dcap
} // namespace client
} // namespace ecs
#endif // __ECS_CLIENT_DERG_H__