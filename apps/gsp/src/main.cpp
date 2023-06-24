#include <ecs/server/sep/world.hpp>
#include <https/server/server.hpp>
#include <iostream>
#include <utilities/utilities.hpp>

std::string g_program_path;

int main(int argc, char **argv) {
  g_program_path = psu::utilities::getProgramPath(argv);

  World::getInstance();

  HttpsServer server("0.0.0.0", 8080, g_program_path, 8);
}
