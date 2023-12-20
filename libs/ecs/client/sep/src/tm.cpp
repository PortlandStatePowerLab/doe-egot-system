#include <ecs/client/sep/tm.hpp>
#include <ecs/singleton/clock.hpp>
#include <iostream>
#include <sep/xml/time_adapter.hpp>
#include <trust/https/client.hpp>
#include <utilities/utilities.hpp>

ecs::client::tm::Module::Module(flecs::world &world) {
  world.module<Module>();

  world.component<sep::Time>();

  world.observer<sep::Time, ecs::singleton::Clock>("time")
      .term_at(2)
      .singleton()
      .event(flecs::OnSet)
      .each([](flecs::entity e, sep::Time &tm, ecs::singleton::Clock &clock) {
        std::cout << "current time=" << tm.current_time << " , " << clock.utc
                  << std::endl;
        clock.offset = tm.current_time - clock.utc;
        std::cout << "Event Time: offset=" << clock.offset << std::endl;
      });
};
