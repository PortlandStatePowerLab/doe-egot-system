#include "utilities/utilities.hpp"
#include <boost/filesystem.hpp>
#include <boost/tokenizer.hpp>
#include <cstddef>
#include <cstdint>
#include <ecs/simulator/waterheater.hpp>
#include <fstream>
#include <iostream>
#include <stdlib.h> /* abs */
#include <string>
#include <time.h>

extern std::string g_program_path;

const std::string TIME_FORMAT = "%Y-%m-%d %H:%M:%S";
const float KG_PER_GALLON = 3.7854;
const float SPECIFIC_HEAT_H2O = 4190;
const float JOULE_PER_WATT_HOUR = 3600;
const int SECONDS_PER_DAY = 24 * 60 * 60;

using Sep = boost::char_separator<char>;
using Tokenizer = boost::tokenizer<Sep>;

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

namespace ecs {
namespace simulator {
namespace waterheater {

bool isEventActive(const Event &event) {
  int64_t time = psu::utilities::getTime();
  std::cout << ctime(&time) << std::endl;
  std::cout << ctime(&event.start_time) << std::endl;
  std::cout << ctime(&event.end_time) << std::endl;
  if (time < event.start_time) {
    return false;
  }
  if (time > event.end_time) {
    return false;
  }
  return true;
};

flecs::entity loadSchedule(flecs::world &world, std::string &path) {
  boost::filesystem::path p = path;
  Schedule events;
  events.current_index = 0;
  if (boost::filesystem::exists(p)) {
    std::ifstream file(path);
    std::string line;
    std::string format = "%Y-%m-%d %H:%M:%S";
    while (getline(file, line)) {
      Event event;
      Sep sep{","};
      Tokenizer tok(line, sep);
      size_t col = 0;
      for (const auto &t : tok) {
        switch (col) {
        case 0:
          event.start_time = psu::utilities::parseTime(t, format);
          break;
        case 1:
          event.end_time = psu::utilities::parseTime(t, format);
          break;
        case 3:
          event.gallons_per_second = stof(t);
          break;
        }
        col++;
      }
      events.events.push_back(event);
    }
    return world.entity().set<Schedule>(events);
  } else {
    std::cout << p << " does not exist\n";
    return world.entity().set<Schedule>(events);
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
        int current = psu::utilities::getTime();
        while (current > events.events[events.current_index].start_time) {
          if (events.current_index < events.events.size() - 1) {
            events.current_index++;
          }
          if (events.current_index == events.events.size()) {
            events.current_index = 0;
          }
        }
        bool active_event =
            isEventActive(events.events.at(events.current_index));
      });

  // world.system<Power, Temperature>("heating").each(
  //     [](flecs::entity e, Power &power, Temperature &temp) {
  //       std::cout << "Checking schedule" << std::endl;
  //     });

  // world.system<Event, Temperature>("water draw")
  //     .each([](flecs::entity e, Event &event, Temperature &temp) {
  //       std::cout << "Checking temperature" << std::endl;
  //     });

  // world.system<State, Temperature>("operating mode")
  //     .each([](flecs::entity e, State &state, Temperature &temp) {
  //       std::cout << "Checking state" << std::endl;
  //     });
};

} // namespace waterheater
} // namespace simulator
} // namespace ecs
