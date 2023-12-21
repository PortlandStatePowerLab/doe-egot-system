#include <ecs/client/cta2045/commodity.hpp>
#include <https/client/client.hpp>
#include <iostream>
#include <string>
#include <trust/cta2045/trust_device.hpp>
#include <utilities/utilities.hpp>
std::string g_program_path;

int main(int argc, char **argv) {
  std::cout << "Starting DCM for AOSmith water heater\n";
  g_program_path = psu::utilities::getProgramPath(argv);

  flecs::world ecs;
  ecs.import <ecs::client::commodity::Module>();
  cea2045::cea2045CommodityData commodity_data;
  ecs.entity().set<cea2045::cea2045CommodityData>(commodity_data);

  https::Context dtm_ctx = {"1", g_program_path, "0.0.0.0", "8090"};
  trust::cta2045Device::getInstance("/ttyAMA0", dtm_ctx);

  ecs.app().target_fps(1).run();
  return 0;
}
