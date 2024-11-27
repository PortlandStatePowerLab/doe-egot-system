#include <ecs/client/sep/rsp.hpp>
#include <ecs/singleton/clock.hpp>
#include <sep/xml/response_adapter.hpp>
#include <trust/https/client.hpp>
#include <utilities/utilities.hpp>

ecs::client::rsp::Module::Module(flecs::world &world) {
  world.module<Module>();

  world.component<sep::Response>();

  world.observer<sep::Response, ecs::singleton::Clock>("time")
      .term_at(2)
      .singleton()
      .event(flecs::OnSet)
      .each([](flecs::entity e, sep::Response &rsp,
               ecs::singleton::Clock &clock) {
        std::cout << "Event Response : =" << std::endl;
      });
};
