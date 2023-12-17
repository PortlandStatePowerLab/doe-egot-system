#include <ecs/server/sep/world.hpp>
#include <https/client/single_client.hpp>
#include <https/server/server.hpp>
#include <iostream>
#include <utilities/utilities.hpp>

std::string g_program_path;

int main(int argc, char **argv) {
  g_program_path = psu::utilities::getProgramPath(argv);

  ecs::server::World::getInstance();

  https::Context me_ctx = {"1", g_program_path, "127.0.0.1", "9000"};
  https::SingleClient::getInstance(me_ctx);

  auto resp = https::SingleClient::getInstance().Get("/time");
  std::string msg = boost::beast::buffers_to_string(resp.body().data());
  std::cout << resp << std::endl;

  resp = https::SingleClient::getInstance().Get("/groups");
  msg = boost::beast::buffers_to_string(resp.body().data());
  std::cout << resp << std::endl;

  resp = https::SingleClient::getInstance().Get("/services");
  msg = boost::beast::buffers_to_string(resp.body().data());
  std::cout << resp << std::endl;

  HttpsServer server("0.0.0.0", 8080, g_program_path, 8);
}
