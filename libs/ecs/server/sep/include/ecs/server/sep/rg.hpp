#ifndef __GSP_ECS_RG_H__
#define __GSP_ECS_RG_H__

#include <boost/property_tree/ptree.hpp>
#include <flecs.h>
#include <sep/models/registration.hpp>
#include <sep/models/time.hpp>
#include <string>

namespace ecs {
namespace server {
namespace rg {

struct Area {
  std::string id;
};

///
/// this module establishes the Registration resources a a component within the
/// ECS world
///
/// It is also responsible for requesting groups from a Grid Operator that
/// establishes the heirachical topolgy of the system
///
/// It also will syncronize with the Grid Operator Time by setting the offset
///
struct Module {
  Module(flecs::world &world);

  ///
  /// generate the Registration resource for all clients registered with the
  /// system
  ///
  void generateRegistration(flecs::world &world);
};

} // namespace rg
} // namespace server
} // namespace ecs
#endif // __GSP_ECS_RG_H__
