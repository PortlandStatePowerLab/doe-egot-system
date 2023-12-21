#ifndef __DCM_CTA2045_MODULE_H__
#define __DCM_CTA2045_MODULE_H__

#include <flecs.h>

namespace ecs {
namespace client {
namespace commodity {
///
/// this module
///
struct Module {
  Module(flecs::world &ecs);
};
} // namespace commodity
} // namespace client
} // namespace ecs
#endif // __DCM_CTA2045_MODULE_H__
