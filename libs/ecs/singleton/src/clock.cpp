#include <boost/date_time/local_time/local_time.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <ecs/singleton/clock.hpp>
#include <iostream>
#include <utilities/utilities.hpp>

void ecs::singleton::generateClock(flecs::world &world) {
  boost::posix_time::ptime local(boost::posix_time::second_clock::local_time());
  boost::posix_time::ptime universal(
      boost::posix_time::second_clock::universal_time());
  ecs::singleton::Clock clock{};
  clock.utc = boost::posix_time::to_time_t(universal);
  clock.local = boost::posix_time::to_time_t(local);
  world.component().set<ecs::singleton::Clock>(clock);
};

ecs::singleton::Module::Module(flecs::world &world) {
  world.module<Module>();

  world.component<Clock>();

  world.system<Clock>("clock").each([](flecs::entity e, Clock &clock) {
    boost::posix_time::ptime local(
        boost::posix_time::second_clock::local_time());
    boost::posix_time::ptime universal(
        boost::posix_time::second_clock::universal_time());
    clock.utc = boost::posix_time::to_time_t(universal);
    clock.local = boost::posix_time::to_time_t(local);
    std::cout << "clock utc : " << clock.utc << std::endl;
    std::cout << "clock local : " << clock.local << std::endl;
  });
};