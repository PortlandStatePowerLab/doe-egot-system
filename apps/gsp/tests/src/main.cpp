#include <gtest/gtest.h>
#include <string>
#include <fstream>
#include <https/server/server.hpp>
#include <https/client/single_client.hpp>
#include <sep/xml/adapter.hpp>
#include <ecs/server/sep/world.hpp>
#include <utilities/utilities.hpp>

std::string g_program_path;

void func (){
    HttpsServer server("0.0.0.0", 8080, g_program_path, 4);
}

int main(int argc, char **argv) 
{
    g_program_path = psu::utilities::getProgramPath(argv);

    https::Context ctx = {"1", g_program_path, "0.0.0.0", "8080"};
    ctx.id = "1";
    ctx.host = "0.0.0.0";
    ctx.port = "8080";
    ctx.root = g_program_path;

    // init context so other calls don't need it
    https::SingleClient::getInstance(ctx);
    
    // run server in seperate thread and detach for auto cleanup
    std::thread first(func);
    first.detach();

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}