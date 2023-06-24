#include <ecs/singleton/clock.hpp>
#include <iostream>
#include <utilities/utilities.hpp>

ecs::singleton::Module::Module(flecs::world &world) {
  world.module<Module>();

  world.component<Clock>();

  world.system<Clock>("clock").each([](flecs::entity e, Clock &clock) {
    uint64_t time = psu::utilities::getTime();
    clock.time = time + clock.offset;
    std::cout << "Clock : " << clock.time << std::endl;
  });
};