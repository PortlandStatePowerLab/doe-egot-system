#ifndef __ECS_SIMULATOR_WATERHEATER__
#define __ECS_SIMULATOR_WATERHEATER__

#include <cstdint>
#include <flecs.h>
#include <initializer_list>
#include <string>
#include <vector>

namespace ecs {
namespace simulator {
namespace waterheater {

struct Power {
  float watts;
};

struct Temperature {
  float fahrenheit;
};

struct Event {
  int64_t start_time;
  int64_t end_time;
  float gallons_per_second;
};

struct Schedule {
  size_t current_index;
  std::vector<Event> events;
};

enum class State {
  NORMAL = 1,
  SHED = 2,
  END_SHED = 3,
  LOAD_UP = 4,
  CRITICAL_PEAK = 5
};

struct Nameplate {
  uint16_t gallons;
  uint16_t temperature_setpoint;
  uint16_t inlet_temperature;
  uint16_t power;
};

flecs::entity loadSchedule(flecs::world &world, std::string &path);

struct Module {
  Module(flecs::world &world);
};

} // namespace waterheater
} // namespace simulator
} // namespace ecs

#endif // __ECS_SIMULATOR_WATERHEATER__