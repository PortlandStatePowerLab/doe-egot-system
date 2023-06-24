#include <cstdint>
#include <ecs/client/sep/tm.hpp>
#include <iostream>
#include <sep/xml/time_adapter.hpp>
#include <trust/https/client.hpp>
#include <utilities/utilities.hpp>

ecs::client::tm::Module::Module(flecs::world &world) {
  world.module<Module>();

  world.component<sep::Time>();
  world.component<Clock>();

  world.system<Clock>("clock").each([](flecs::entity e, Clock &clock) {
    uint64_t time = psu::utilities::getTime();
    clock.time = time + clock.offset;
  });

  world.observer<sep::Time, Clock>("time")
      .event(flecs::OnSet)
      .term_at(2)
      .singleton()
      .each([](flecs::entity e, sep::Time &tm, Clock &clock) {
        std::cout << "Event Time" << std::endl;
      });
};