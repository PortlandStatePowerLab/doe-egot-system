#ifndef __GSP_ECS_RG_H__
#define __GSP_ECS_RG_H__

#include <flecs.h>
#include <sep/models/registration.hpp>
#include <string>

namespace gsp {
namespace rg {
void generateRegistration(flecs::world &world);
struct Fingerprint {
  std::string lfdi;
};

struct Module {
  Module(flecs::world &world);
};

} // namespace rg
} // namespace gsp
#endif // __GSP_ECS_RG_H__