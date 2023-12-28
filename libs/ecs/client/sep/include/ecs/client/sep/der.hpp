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
  static void getDERList(flecs::entity e,
                                  sep::DERListLink &link);
  ///
  /// update the DER resource and all its links
  ///
  static void updateDER(flecs::entity e,
                                     sep::DER &dderc);
};
} // namespace dcap
} // namespace client
} // namespace ecs
#endif // __ECS_CLIENT_DER_H__