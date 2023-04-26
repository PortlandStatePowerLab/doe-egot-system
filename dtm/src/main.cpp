#include <iostream>
#include <stdlib.h>
#include <thread>         // std::thread
#include <string>
#include <dtm/dtm_server.hpp>
#include <utilities/utilities.hpp>

std::string g_program_path;

void spawnDTM(int argc, char **argv)
{
    DistributedTrustManagment dtm(argc, argv);
};

int main(int argc, char **argv)
{
    std::cout << "Communication demo...\n";
    g_program_path = psu::utilities::getProgramPath(argv);
    std::cout << "Parent Path : " << g_program_path << std::endl;

    std::thread dtm(spawnDTM, argc, argv);

    dtm.join();
    
    return 0;
}
