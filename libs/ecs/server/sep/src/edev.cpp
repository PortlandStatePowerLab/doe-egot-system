#include <ecs/server/sep/edev.hpp>
#include <sep/xml/utilities.hpp>
#include <utilities/utilities.hpp>

std::string gsp::edev::generateURI(const sep::EndDevice &edev) {
  return edev.href + "/" + xml::util::Hexify(edev.lfdi);
};

gsp::edev::Module::Module(flecs::world &world) {
  world.module<Module>();
  world.component<sep::EndDevice>();
};