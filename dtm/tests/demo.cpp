#include <boost/python.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include <iostream>
#include <thread>         // std::thread
#include <chrono>         // std::chrono::seconds
#include <string>

#include <https/combined_client.hpp>
#include <https/combined_client.hpp>
#include <https/https_server.hpp>
#include <dtm/dtm_server.hpp>

inline std::string GetParentPath(char** arg)
{
    std::string path = arg[0];
    std::size_t found = path.find_last_of("/\\");
    return path.substr(0,found);
};

inline void ResetConfig (boost::property_tree::ptree *pt)
{
    pt->put("DTM.port", 4430);
    pt->put("DCM.cert", "/certs/client1.crt");
    pt->put("DCM.key", "/certs/private/client1.crt");
};

void SpawnDTM(int argc, char **argv)
{
    DistributedTrustManagment dtm(argc, argv);
};

void SpawnGSP(const boost::property_tree::ptree &pt, const std::string &root)
{
    std::string host = pt.get<std::string>("GSP.host");
    int port = pt.get<int>("GSP.port");
    HttpsServer gsp(host, port, root);
    try
    {
        gsp.Run();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
};

void SpawnDCM(int argc, char **argv)
{
    DistributedTrustManagment dtm(argc, argv);
};

void Demo (const boost::property_tree::ptree pt, const std::string &root)
{
    std::string gsp_host = pt.get<std::string>("GSP.host");
    std::string gsp_port = pt.get<std::string>("GSP.port");

    std::string dtm_host = pt.get<std::string>("DTM.host");
    std::string dtm_port = pt.get<std::string>("DTM.port");

    CombinedHttpsClient dcm(
            root, gsp_host, gsp_port,
            root, dtm_host, dtm_port);

    dcm.Get("/dcap");
    dcm.Get("/tm");
    dcm.Get("/edev");
  
    std::string freq = R"(<?xml version="1.0" encoding="utf-8"?>
    <FlowReservationRequest href="http://uri1" xmlns="urn:ieee:std:2030.5:ns">
    <mRID>0FB7</mRID>
    <description>description1</description>
    <version>0</version>
    <creationTime>1</creationTime>
    <durationRequested>0</durationRequested>
    <energyRequested>
        <multiplier>1</multiplier>
        <value>-140737488355328</value>
    </energyRequested>
    <intervalRequested>
        <duration>0</duration>
        <start>1</start>
    </intervalRequested>
    <powerRequested>
        <multiplier>1</multiplier>
        <value>1</value>
    </powerRequested>
    <RequestStatus>
        <dateTime>1</dateTime>
        <requestStatus>0</requestStatus>
    </RequestStatus>
    </FlowReservationRequest>)";
    dcm.Post("/freq", freq);
    dcm.Get("/fres");
    dcm.Get("/sdev");
};

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout << "ERROR: must provide number of dcm to demo.\n";
        std::cout << "\tExample: ./demo 10\n";
        return 0;
    }

    std::string program_path = GetParentPath(argv);
    size_t client_count = atoi(argv[1]);

    std::string config = program_path + "/../../config.ini";

    // Create empty property tree object
    boost::property_tree::ptree pt;
    boost::property_tree::read_ini(config, pt);

    ResetConfig(&pt);

    std::thread gsp (SpawnGSP, pt, program_path);

    std::vector <std::thread> dcm_pool;
    dcm_pool.reserve(client_count);

    std::vector <std::thread> dtm_pool;
    dtm_pool.reserve(client_count);
    std::thread t1(SpawnDTM, argc, argv);
    dtm_pool.emplace_back(std::move(t1));

    std::this_thread::sleep_for (std::chrono::seconds(1));
    for (size_t i = 0; i < client_count; i++)
    {
        int dtm_port = pt.get<int>("DTM.port") + i;
        //pt.put("DTM.port", dtm_port);
        //boost::property_tree::write_ini(config, pt);



        std::thread t2(Demo, pt, program_path);
        dcm_pool.emplace_back(std::move(t2));
    } 

    // synchronize dcm:
    for (auto &t : dcm_pool)
    {
        t.join();
    }
    
    // detach servers:
    for (auto &t : dtm_pool)
    {
        t.detach();
    }
    
    gsp.detach(); 
    return 0;    
}