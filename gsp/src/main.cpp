#include <iostream>
#include <https/https_server.hpp>
#include <utilities/utilities.hpp>
#include <xml/adapter.hpp>
#include <sep/rg.hpp>
#include <utilities/utilities.hpp>
#include <boost/filesystem.hpp>
#include <boost/date_time/time_zone_base.hpp>
#include <boost/date_time/local_time/local_time.hpp>
#include <boost/date_time/posix_time/posix_time.hpp> 

std::string g_program_path;

int main(int argc, char **argv) 
{
    g_program_path = psu::utilities::getProgramPath(argv);

    flecs::world ecs;
    ecs.import<gsp::rg::Module>();
    
    HttpsServer server("0.0.0.0", 8080, g_program_path, 8);

    std::cout << "Shouldn't see this" << std::endl;
}
