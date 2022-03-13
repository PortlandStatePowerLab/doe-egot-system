#include <gtest/gtest.h>
#include <string>
#include <fstream>
#include <https/https_server.hpp>
#include <https/https_client.hpp>
#include <ieee-2030.5/models.hpp>
#include <xml/adapter.hpp>
#include <world/world.hpp>

std::string g_program_path;

std::string readFile (const std::string& file)
{
    std::string content;

    std::ifstream ifs(file);
    if (ifs)
    {
        std::ostringstream oss;
        oss << ifs.rdbuf();

        content = oss.str();
    }
    else
    {
        content = "";
    };
    ifs.close();
    return content;
};

void GetParentPath(char** arg)
{
    g_program_path = arg[0];
    std::size_t found = g_program_path.find_last_of("/\\");
    g_program_path = g_program_path.substr(0,found);
};

int main(int argc, char **argv) 
{
    GetParentPath(argv);
    World* world = World::getInstance();

    // read in the sample file
    std::string sample = readFile(g_program_path + "/sep_xml/DeviceCapability.xml");
    sep::DeviceCapability dcap;
    xml::Parse(sample, &dcap);

    world->world.entity("/dcap")
        .set<sep::DeviceCapability>(dcap);

    sample = readFile(g_program_path + "/sep_xml/SelfDevice.xml");
    sep::SelfDevice sdev;
    xml::Parse(sample, &sdev);

    world->world.entity("/sdev")
        .set<sep::SelfDevice>(sdev);

    sample = readFile(g_program_path + "/sep_xml/EndDevice.xml");
    sep::EndDevice edev;
    xml::Parse(sample, &edev);

    // TODO: This will need to be handled during the ECS registration system
    world->world.entity("/0FB7/edev")
        .set<sep::EndDevice>(edev);

    sample = readFile(g_program_path + "/sep_xml/Registration.xml");
    sep::Registration rg;
    xml::Parse(sample, &rg);

    // TODO: This will need to be handled during the ECS registration system
    world->world.entity("/0FB7/rg")
        .set<sep::Registration>(rg);
    
    // run server in seperate thread and detach for auto cleanup
    HttpsServer* https_server = new HttpsServer("0.0.0.0", 8080, g_program_path);
    std::thread first(&HttpsServer::Run, https_server);
    first.detach();

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
