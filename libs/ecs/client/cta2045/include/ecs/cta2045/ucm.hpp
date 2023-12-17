#ifndef __DCM_CTA2045_MODULE_H__
#define __DCM_CTA2045_MODULE_H__

#include <flecs.h>

namespace ecs {
namespace cta2045 {
namespace ucm {
///
/// this module
///
struct Module {
  Module(flecs::world &ecs);
};
} // namespace ucm
} // namespace cta2045
} // namespace ecs
#endif // __DCM_CTA2045_MODULE_H__
