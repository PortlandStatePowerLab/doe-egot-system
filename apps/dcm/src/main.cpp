#include <ecs/client/sep/dcap.hpp>
#include <ecs/client/sep/der.hpp>
#include <ecs/client/sep/edev.hpp>
#include <ecs/client/sep/rg.hpp>
#include <ecs/client/sep/tm.hpp>
#include <ecs/singleton/clock.hpp>
#include <https/client/single_client.hpp>
#include <iostream>
#include <sep/models/device_capability.hpp>
#include <string>
#include <trust/https/client.hpp>
#include <utilities/utilities.hpp>

std::string g_program_path;

int main(int argc, char **argv) {
  std::cout << "Starting Distributed Control Module...\n";
  g_program_path = psu::utilities::getProgramPath(argv);
  std::cout << "\tpath : " << g_program_path << std::endl;

  std::string index = argv[1];

  https::Context me_ctx = {"1", g_program_path, "0.0.0.0", "9000"};
  https::Context gsp_ctx = {"1", g_program_path, "0.0.0.0", "8080"};
  https::Context dtm_ctx = {"1", g_program_path, "0.0.0.0", "8090"};

  std::cout << "\tgsp client on " << gsp_ctx.host << ":" << gsp_ctx.port
            << "\n";

  std::cout << "\tdtm client on " << dtm_ctx.host << ":" << dtm_ctx.port
            << "\n";

  flecs::world ecs;
  ecs.import <ecs::singleton::Module>();
  ecs::singleton::generateClock(ecs);

  https::SingleClient::getInstance(me_ctx);
  trust::HttpsClient::getInstance(gsp_ctx, dtm_ctx);
  ecs.import <ecs::client::dcap::Module>();
  ecs.import <ecs::client::edev::Module>();
  ecs.import <ecs::client::der::Module>();
  ecs.import <ecs::client::rg::Module>();
  ecs.import <ecs::client::tm::Module>();

  sep::DeviceCapabilityLink dcap_link;
  dcap_link.href = "/dcap";

  auto e = ecs.entity();
  e.set<sep::DeviceCapabilityLink>(dcap_link);

  ecs.app().target_fps(1).run();

  return 0;
}
