#include <iostream>
#include <https/server/server.hpp>
#include <utilities/utilities.hpp>
#include <ecs/server/sep/world.hpp>

std::string g_program_path;

int main(int argc, char **argv) 
{
    g_program_path = psu::utilities::getProgramPath(argv);

    World::getInstance();
    
    HttpsServer server("0.0.0.0", 8080, g_program_path, 8);
}
