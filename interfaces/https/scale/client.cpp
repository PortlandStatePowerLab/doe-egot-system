#include <iostream>
#include <https/single_client.hpp>
#include <utilities/utilities.hpp>
#include <chrono>  // for high_resolution_clock

std::string g_program_path;

int main(int argc, char **argv)
{
    g_program_path = psu::utilities::getProgramPath(argv);

    std::string id = argv[1];
    // Record start time
    auto start = std::chrono::high_resolution_clock::now();

    https::Context ctx = {id, g_program_path, "0.0.0.0", "8080"};
    ctx.id = "1";
    ctx.host = "0.0.0.0";
    ctx.port = "8080";
    ctx.root = g_program_path;

    https::SingleClient::getInstance(ctx);

    auto resp = https::SingleClient::getInstance().Get("/dcap");    
    
    // Record end time
    auto finish = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = finish - start;
    std::cout << id << " : " << resp.result() << " in " << elapsed.count() << " seconds \n";

}
