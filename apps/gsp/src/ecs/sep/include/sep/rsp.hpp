#ifndef __GSP_ECS_RSP_H__
#define __GSP_ECS_RSP_H__

#include <flecs.h>
#include <ieee-2030.5/response.hpp>

namespace gsp {
namespace rsp {

struct Module {
  Module(flecs::world &world);
};

} // namespace rsp
} // namespace gsp
#endif // __GSP_ECS_RSP_H__