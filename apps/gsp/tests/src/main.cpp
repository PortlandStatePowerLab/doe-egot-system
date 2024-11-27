#include <chrono>
#include <ecs/server/sep/world.hpp>
#include <gtest/gtest.h>
#include <https/client/single_client.hpp>
#include <https/server/server.hpp>
#include <sep/xml/adapter.hpp>
#include <string>
#include <utilities/utilities.hpp>

using namespace std::chrono_literals;

std::string g_program_path;

void func() { HttpsServer server("0.0.0.0", 8080, g_program_path, 4); }

int main(int argc, char **argv) {
  g_program_path = psu::utilities::getProgramPath(argv);

  ecs::server::World::getInstance();

  https::Context ctx = {"1", g_program_path, "0.0.0.0", "8080"};

  // init context so other calls don't need it
  https::SingleClient::getInstance(ctx);

  // run server in seperate thread and detach for auto cleanup
  std::thread first(func);
  first.detach();

  ::testing::InitGoogleTest(&argc, argv);
  std::this_thread::sleep_for(1s);
  return RUN_ALL_TESTS();
}
