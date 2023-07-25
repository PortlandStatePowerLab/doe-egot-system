#include <boost/filesystem.hpp>
#include <boost/tokenizer.hpp>
#include <ecs/simulator/waterheater.hpp>
#include <iostream>
#include <string>

extern std::string g_program_path;

const std::string TIME_FORMAT = "%Y-%m-%d %H:%M:%S";
const float KG_PER_GALLON = 3.7854;
const float SPECIFIC_HEAT_H2O = 4190;
const float JOULE_PER_WATT_HOUR = 3600;

namespace ecs {
namespace simulator {
namespace waterheater {

float toCelsius(const float &fahrenheit) { return (fahrenheit - 32) / 1.8; };
float toFahrenheit(const float &celsius) { return celsius * 1.8 + 32; };
float toKilograms(const float &gallons) { return KG_PER_GALLON * gallons; };
float heatingEnergy(const float &t2, const float &t1, const float &volume) {
  float c = SPECIFIC_HEAT_H2O;
  float m = toKilograms(volume);
  float delta_temp = toCelsius(t2) - toCelsius(t1);
  return c * m * delta_temp / JOULE_PER_WATT_HOUR;
};

float tempChange(const float &temperature, const float &volume,
                 const float &energy) {
  float c = SPECIFIC_HEAT_H2O;
  float m = toKilograms(volume);
  float t1 = toCelsius(temperature);
  float t2 = (energy * JOULE_PER_WATT_HOUR) / (c * m) + t1;
  return toFahrenheit(t2);
};

void loadSchedule(flecs::world &world, std::string &path) {
  boost::filesystem::path p = path;
  if (boost::filesystem::exists(p)) {
    Schedule events;

  } else {
    std::cout << p << " does not exist\n";
  }
};

Module::Module(flecs::world &world) {

  world.module<Module>();

  world.component<Event>();
  world.component<Schedule>();
  world.component<Nameplate>();
  world.component<State>();
  world.component<Power>();
  world.component<Temperature>();

  world.system<Schedule>("schedule")
      .each([](flecs::entity e, Schedule &events) {
        std::cout << "Checking schedule" << std::endl;
      });

  world.system<Power, Temperature>("heating").each(
      [](flecs::entity e, Power &power, Temperature &temp) {
        std::cout << "Checking schedule" << std::endl;
      });

  world.system<Event, Temperature>("water draw")
      .each([](flecs::entity e, Schedule &events) {
        std::cout << "Checking schedule" << std::endl;
      });

  world.system<State, Temperature>("operating mode")
      .each([](flecs::entity e, Schedule &events) {
        std::cout << "Checking schedule" << std::endl;
      });
};

} // namespace waterheater
} // namespace simulator
} // namespace ecs
