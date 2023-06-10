#include <ecs/server/sep/rsp.hpp>
#include <sep/xml/utilities.hpp>

std::string gsp::rsp::generateURI(const sep::Response &rsp) {
  return "/rsp/" + xml::util::Hexify(rsp.subject);
};
gsp::rsp::Module::Module(flecs::world &world) {
  world.module<Module>();
  world.component<sep::Response>();
};