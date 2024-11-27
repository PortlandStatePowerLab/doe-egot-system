#include <ecs/client/sep/rg.hpp>
#include <iostream>
#include <trust/https/client.hpp>
#include <utilities/utilities.hpp>

ecs::client::rg::Module::Module(flecs::world &world) {
  world.module<Module>();

  world.component<sep::Registration>();

  world.observer<sep::Registration>("registration")
      .event(flecs::OnSet)
      .each([](flecs::entity e, sep::Registration &rg) {
        std::cout << "Event Registration" << std::endl;
      });
};