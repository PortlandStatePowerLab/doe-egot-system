#ifndef __ECS_CLIENT_CDP_H__
#define __ECS_CLIENT_CDP_H__

#include <flecs.h>
#include <sep/models/der_program.hpp>

namespace ecs {
namespace client {
namespace cdp {

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
  static void getCurrentDERProgram(flecs::entity e,
                                  sep::CurrentDERProgramLink &link);
  ///
  /// update the CurrentDERProgram resource and all its links
  ///
  static void updateCurrentDERProgram(flecs::entity e,
                                     sep::DERProgram &dcap);
};
} // namespace dcap
} // namespace client
} // namespace ecs
#endif // __ECS_CLIENT_CDP_H__