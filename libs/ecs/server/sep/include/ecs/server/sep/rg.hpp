#ifndef __GSP_ECS_RG_H__
#define __GSP_ECS_RG_H__

#include <flecs.h>
#include <sep/models/registration.hpp>
#include <string>

namespace gsp {
namespace rg {
struct Group {
  std::string id;
};

struct Area {
  std::string id;
};

void generateRegistration(flecs::world &world);
struct Module {
  Module(flecs::world &world);
};

} // namespace rg
} // namespace gsp
#endif // __GSP_ECS_RG_H__