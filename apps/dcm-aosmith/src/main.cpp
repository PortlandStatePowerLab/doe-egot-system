#include <ecs/client/cta2045/commodity.hpp>
#include <https/client/client.hpp>
#include <iostream>
#include <sep/models/active_power.hpp>
#include <sep/models/real_energy.hpp>
#include <string>
#include <trust/cta2045/trust_device.hpp>
#include <utilities/utilities.hpp>

std::string g_program_path;

int main(int argc, char **argv) {
  std::cout << "Starting DCM for AOSmith water heater\n";
  g_program_path = psu::utilities::getProgramPath(argv);

  flecs::world ecs;
  ecs.import <ecs::client::commodity::Module>();
  ecs.entity().set<sep::ActivePower>({0, 0});
  ecs.entity().set<sep::RealEnergy>({0, 0});
  https::Context dtm_ctx = {"1", g_program_path, "0.0.0.0", "8090"};
  trust::cta2045Device::getInstance("/dev/ttyAMA0", dtm_ctx);
  ecs.app().target_fps(1).run();
  return 0;
}
