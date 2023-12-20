#ifndef __FSA_H__
#define __FSA_H__

#include <flecs.h>

namespace ecs {
namespace client {
namespace fsab {

///
/// this module establishes the FunctionSetAssignmentResource as a component
/// within the ECS world
///
struct Module {
  Module(flecs::world &world);
};

} // namespace fsab
} // namespace client
} // namespace ecs

#endif // __FSA_H__
