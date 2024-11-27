#include <ecs/server/sep/edev.hpp>
#include <sep/xml/utilities.hpp>
#include <utilities/utilities.hpp>

namespace ecs {
namespace server {
namespace edev {
std::string generateURI(const sep::EndDevice &edev) {
  return edev.href + "/" + xml::util::Hexify(edev.lfdi);
};

Module::Module(flecs::world &world) {
  world.module<Module>();
  world.component<sep::EndDevice>();
};
} // namespace edev
} // namespace server
} // namespace ecs
