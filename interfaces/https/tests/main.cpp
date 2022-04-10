#include <gtest/gtest.h>
#include <string>
#include <fstream>
#include <https/https_server.hpp>
#include <https/https_client.hpp>
#include <ieee-2030.5/models.hpp>
#include <xml/adapter.hpp>
#include <world/world.hpp>
#include <utilities/utilities.hpp>

std::string g_program_path;

int main(int argc, char **argv) 
{
    g_program_path = psu::utilities::getProgramPath(argv);
    World* world = World::getInstance();
    
    // run server in seperate thread and detach for auto cleanup
    HttpsServer* https_server = new HttpsServer("0.0.0.0", 8080, g_program_path);
    std::thread first(&HttpsServer::Run, https_server);
    first.detach();

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
