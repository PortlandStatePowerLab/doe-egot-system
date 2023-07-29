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
    getline(file, line); // ignore header
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
        case 2:
          event.gallons_per_second = std::stof(t);
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
        int current = psu::utilities::getTime();
        while (current > events.events[events.current_index].start_time) {
          if (events.current_index < events.events.size() - 1) {
            events.current_index++;
          }
          if (events.current_index == events.events.size()) {
            events.current_index = 0;
          }
        }

        if (isEventActive(events.events.at(events.current_index))) {
          e.set<Event>(events.events.at(events.current_index));
        } else {
          e.remove<Event>();
        }
        e.set<Event>(events.events.at(events.current_index));
      });

  world.system<Event, Temperature, Nameplate>("water draw")
      .each([](flecs::entity e, Event &event, Temperature &temp,
               Nameplate &rating) {
        float t1 = rating.inlet_temperature;
        float t2 = temp.fahrenheit;
        float m1 = event.gallons_per_second;
        float m2 = rating.gallons;
        temp.fahrenheit = (m1 * t1 + m2 * t2) / (m1 + m2);
      });

  world.system<Temperature, Nameplate>("heating")
      .term(State::NORMAL)
      .each([](flecs::entity e, Temperature &temp, Nameplate &rating) {
        std::cout << "Normal mode" << std::endl;
        float upper_bound = rating.temperature_setpoint + 2;
        float lower_bound = rating.temperature_setpoint - 2;

        if (temp.fahrenheit > upper_bound) {
          e.remove<Power>();
        }
        if (temp.fahrenheit < lower_bound) {
          Power power = {};
          power.watts = rating.power;
          e.set<Power>(power);
        }
      });

  world.system<Power, Temperature>("heating")
      .term(State::NORMAL)
      .each([](flecs::entity e, Power &power, Temperature &temp) {
        std::cout << "Normal low water heater temp" << std::endl;
      });

  // world.system<State, Temperature>("operating mode")
  //     .each([](flecs::entity e, State &state, Temperature &temp) {
  //       std::cout << "Checking state" << std::endl;
  //     });
};

} // namespace waterheater
} // namespace simulator
} // namespace ecs
