#ifndef __ECS_CLIENT_DERS_H__
#define __ECS_CLIENT_DERS_H__

#include <flecs.h>
#include <sep/models/der_status.hpp>

namespace ecs {
namespace client {
namespace ders {

///
/// This module sets the startup system for all IEEE 2030.5 resources by
/// requesting the DERProgram and updating the links it contains. It also
/// establishes observers to make requests when the links are modified to keep
/// other modules updated.
///
struct Module {
  Module(flecs::world &world);

  ///
  /// request the DERProgram resource from an IEEE 2030.5 Server
  ///
  static void getDERProgram(flecs::entity e,
                                  sep::DERStatusLink &link);
  ///
  /// update the DERProgram resource and all its links
  ///
  static void updateDERProgram(flecs::entity e,
                                     sep::DERStatus &ders);
};
} // namespace dcap
} // namespace client
} // namespace ecs
#endif // __ECS_CLIENT_DERS_H__