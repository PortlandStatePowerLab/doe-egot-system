#ifndef __GSP_ECS_RSP_H__
#define __GSP_ECS_RSP_H__

#include <flecs.h>
#include <sep/models/response.hpp>

namespace gsp {
namespace rsp {

std::string generateURI(const sep::Response &rsp);
struct Module {
  Module(flecs::world &world);
};

} // namespace rsp
} // namespace gsp
#endif // __GSP_ECS_RSP_H__