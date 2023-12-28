#ifndef __ECS_CLIENT_FSA_H__
#define __ECS_CLIENT_FSA_H__

#include <flecs.h>
#include <sep/models/function_set_assignments.hpp>

namespace ecs {
namespace client {
namespace fsa {

///
/// This module sets the startup system for all IEEE 2030.5 resources by
/// requesting the FunctionSetAssignment and updating the links it contains. It also
/// establishes observers to make requests when the links are modified to keep
/// other modules updated.
///
struct Module {
  Module(flecs::world &world);

  ///
  /// request the FunctionSetAssignment resource from an IEEE 2030.5 Server
  ///
  static void getFunctionSetAssignment(flecs::entity e,
                                  sep::FunctionSetAssignmentsListLink &link);
  ///
  /// update the FunctionSetAssignment resource and all its links
  ///
  static void updateFunctionSetAssignment(flecs::entity e,
                                     sep::FunctionSetAssignments &fsa);
};
} // namespace dcap
} // namespace client
} // namespace ecs
#endif // __ECS_CLIENT_FSA_H__