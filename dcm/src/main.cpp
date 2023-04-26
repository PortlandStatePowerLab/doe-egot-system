#include <iostream>
#include <string>
#include <sep/dcap.hpp>
#include <trust_https/trust_https.hpp>
#include <utilities/utilities.hpp>

std::string g_program_path;

int main(int argc, char **argv)
{
    std::cout << "Starting Distributed Control Module...\n";
    g_program_path = psu::utilities::getProgramPath(argv);
    std::cout << "\tpath : " << g_program_path << std::endl;

    
    https::Context gsp_ctx = {"1", g_program_path, "0.0.0.0", "8080"};
    https::Context dtm_ctx = {"1", g_program_path, "0.0.0.0", "8090"};

    std::cout 
        << "\tgsp client on " 
        << gsp_ctx.host << ":" << gsp_ctx.port << "\n";

    std::cout 
        << "\tdtm client on " 
        << dtm_ctx.host << ":" << dtm_ctx.port << "\n";

    trust::HttpsClient::getInstance(gsp_ctx, dtm_ctx);

    flecs::world ecs;

    ecs.import<sep::dcap::Module>();

    sep::dcap::PollRate poll_rate;
    poll_rate.seconds = 5;

    sep::dcap::EndDeviceListLink edev;
    edev.all = 1;
    edev.href = "/href";

    auto test = ecs.entity<sep::dcap::Test>();
    test.set<sep::dcap::PollRate>(poll_rate);
    test.set<sep::dcap::EndDeviceListLink>(edev);

    auto json = ecs.to_json();
    std::cout << json << std::endl << std::endl;

    ecs.app()
        .target_fps(1)
        .run();

    return 0;
}
