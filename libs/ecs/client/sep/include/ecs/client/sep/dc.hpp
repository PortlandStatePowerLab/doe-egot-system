#ifndef __ECS_CLIENT_DC_H__
#define __ECS_CLIENT_DC_H__

#include <flecs.h>
#include <sep/models/der_control.hpp>

namespace ecs {
namespace client {
namespace dc {

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
  static void getDERControl(flecs::entity e, sep::DERControl &link);

  ///
  /// request the DERControl resource from an IEEE 2030.5 Server
  ///
  static void getDERCurve(flecs::entity e, sep::DERCurveLink &link);

  ///
  /// update the DERControl resource and all its links
  ///
  static void updateDERControl(flecs::entity e, sep::DERControl &dcap);
};
} // namespace dc
} // namespace client
} // namespace ecs
#endif // __ECS_CLIENT_DC_H__