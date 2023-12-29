#ifndef __GSP_ECS_DER_H__
#define __GSP_ECS_DER_H__

#include <flecs.h>

namespace ecs {
namespace server {
namespace der {

///
/// this module establishes the DER and all its sub resoruces as a component
/// within the ECS world
///
struct Module {
  Module(flecs::world &world);
};

} // namespace der
} // namespace server
} // namespace ecs
#endif // __GSP_ECS_DER_H__
