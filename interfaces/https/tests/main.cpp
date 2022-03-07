#include <gtest/gtest.h>
#include <string>
#include <https/https_server.hpp>
#include <https/https_client.hpp>

std::string g_program_path;

void GetParentPath(char** arg)
{
    g_program_path = arg[0];
    std::size_t found = g_program_path.find_last_of("/\\");
    g_program_path = g_program_path.substr(0,found);
};

int main(int argc, char **argv) 
{
    GetParentPath(argv);

    // run server in seperate thread and detach for auto cleanup
    HttpsServer* https_server = new HttpsServer("0.0.0.0", 8080, g_program_path);
    std::thread first(&HttpsServer::Run, https_server);
    first.detach();

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
