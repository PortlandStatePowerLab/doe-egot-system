#ifndef __ECS_CLIENT_DDERC_H__
#define __ECS_CLIENT_DDERC_H__

#include <flecs.h>
#include <sep/models/der_control.hpp>

namespace ecs {
namespace client {
namespace dderc {

///
/// This module sets the startup system for all IEEE 2030.5 resources by
/// requesting the CurrentDERProgram and updating the links it contains. It also
/// establishes observers to make requests when the links are modified to keep
/// other modules updated.
///
struct Module {
  Module(flecs::world &world);

  ///
  /// request the CurrentDERProgram resource from an IEEE 2030.5 Server
  ///
  static void getDefaultDERControl(flecs::entity e,
                                  sep::DefaultDERControlLink &link);
  ///
  /// update the CurrentDERProgram resource and all its links
  ///
  static void updateDefaultDERControl(flecs::entity e,
                                     sep::DERControl &dderc);
};
} // namespace dcap
} // namespace client
} // namespace ecs
#endif // __ECS_CLIENT_DDERC_H__