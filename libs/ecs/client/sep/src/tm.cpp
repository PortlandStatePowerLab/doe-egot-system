#include <ecs/client/sep/tm.hpp>
#include <iostream>
#include <sep/xml/time_adapter.hpp>
#include <trust/https/client.hpp>
#include <utilities/utilities.hpp>

ecs::client::tm::Module::Module(flecs::world &world) {
  world.module<Module>();

  world.component<sep::Time>();

  world.observer<sep::Time>("time")
      .event(flecs::OnSet)
      .each([](flecs::entity e, sep::Time &tm) {
        std::cout << "Event Time" << std::endl;
      });
};