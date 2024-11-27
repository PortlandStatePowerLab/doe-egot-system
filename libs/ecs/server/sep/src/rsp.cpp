#include <ecs/server/sep/rsp.hpp>
#include <sep/xml/utilities.hpp>

namespace ecs {
namespace server {
namespace rsp {
std::string generateURI(const sep::Response &rsp) {
  return "/rsp/" + xml::util::Hexify(rsp.subject);
};

Module::Module(flecs::world &world) {
  world.module<Module>();
  world.component<sep::Response>();
};
} // namespace rsp
} // namespace server
} // namespace ecs
