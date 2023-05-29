#ifndef __GSP_ECS_RG_H__
#define __GSP_ECS_RG_H__

#include <string>
#include <flecs.h>
#include <sep/models/registration.hpp>

namespace gsp {
namespace rg {

struct Fingerprint {
  std::string lfdi;
};

struct Module {
  Module(flecs::world &world);
};

} // namespace rg
} // namespace gsp
#endif // __GSP_ECS_RG_H__