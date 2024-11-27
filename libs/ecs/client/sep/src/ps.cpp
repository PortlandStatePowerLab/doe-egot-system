#include "sep/models/power_status.hpp"
#include <ecs/client/sep/ps.hpp>
#include <ecs/singleton/clock.hpp>
#include <iostream>
#include <sep/xml/power_status_adapter.hpp>
#include <trust/https/client.hpp>
#include <utilities/utilities.hpp>

ecs::client::ps::Module::Module(flecs::world &world) {
  world.module<Module>();

  world.component<sep::PowerStatus>();

  world.observer<sep::PowerStatus, ecs::singleton::Clock>("time")
      .term_at(2)
      .singleton()
      .event(flecs::OnSet)
      .each([](flecs::entity e, sep::PowerStatus &ps,
               ecs::singleton::Clock &clock) {
        std::cout << "Event PowerStatus : =" << std::endl;
      });
};
