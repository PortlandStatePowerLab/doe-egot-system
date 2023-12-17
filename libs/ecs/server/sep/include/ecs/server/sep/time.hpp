#ifndef __GSP_ECS_TIME_H__
#define __GSP_ECS_TIME_H__

#include <flecs.h>
#include <sep/models/time.hpp>

namespace ecs {
namespace server {
namespace time {

///
/// this module established the Time resources as a component within the ECS
/// world
///
struct Module {
  Module(flecs::world &world);

  ///
  /// This function creates a Time resource to act as the clock for all clients
  ///
  static void generateTime(flecs::world &world);

  ///
  /// updates the Time resource ever second for all clients rather than updating
  /// every time the server recieves a request
  ///
  static void updateTime(flecs::entity e, sep::Time &tm);
};

} // namespace time
} // namespace server
} // namespace ecs
#endif // __GSP_ECS_TIME_H__
