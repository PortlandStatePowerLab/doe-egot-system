#include <ecs/client/sep/rsps.hpp>
#include <ecs/singleton/clock.hpp>
#include <sep/xml/response_set_adapter.hpp>
#include <trust/https/client.hpp>
#include <utilities/utilities.hpp>

ecs::client::rsps::Module::Module(flecs::world &world) {
  world.module<Module>();

  world.component<sep::ResponseSet>();

  world.observer<sep::ResponseSet, ecs::singleton::Clock>("time")
      .term_at(2)
      .singleton()
      .event(flecs::OnSet)
      .each([](flecs::entity e, sep::ResponseSet &rsps,
               ecs::singleton::Clock &clock) {
        std::cout << "Event ResponseSet : =" << std::endl;
      });
};
