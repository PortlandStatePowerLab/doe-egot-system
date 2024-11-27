#ifndef __GSP_ECS_RSP_H__
#define __GSP_ECS_RSP_H__

#include <flecs.h>
#include <sep/models/response.hpp>

namespace ecs {
namespace server {
namespace rsp {
///
/// maps the ECS path to a uri for HTTPS client requests
///
std::string generateURI(const sep::Response &rsp);

///
/// this module sets the Response resource as a component within the ECS world
///
struct Module {
  Module(flecs::world &world);
};

} // namespace rsp
} // namespace server
} // namespace ecs
#endif // __GSP_ECS_RSP_H__
