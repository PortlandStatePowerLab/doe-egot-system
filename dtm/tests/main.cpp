#include <gtest/gtest.h>
#include <boost/python.hpp>
#include <iostream>
#include <stdlib.h>
#include <thread>         // std::thread
#include <chrono>         // std::chrono::seconds
#include <string>

#include <https/combined_client.hpp>
#include <https/combined_client.hpp>
#include <https/https_server.hpp>

using namespace boost::python;

std::string g_program_path;

void GetParentPath(char** arg)
{
    g_program_path = arg[0];
    std::size_t found = g_program_path.find_last_of("/\\");
    g_program_path = g_program_path.substr(0,found);
};

void SpawnGSP()
{
    HttpsServer gsp("0.0.0.0", 443, g_program_path);
    try
    {
        gsp.Run();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
};

void SpawnDTM(const std::string &file_path, int argc, wchar_t **wargv)
{
try
    {
        Py_Initialize();
        PySys_SetArgv(argc, wargv);
        object _mainModule = import("__main__");
        object _mainNamespace = _mainModule.attr("__dict__");

        //Testing executing a python script file
        //exec_file("script.py", _mainNamespace, _mainNamespace);
        //Run a simple file
        FILE* PScriptFile = fopen(file_path.c_str(), "r");
        if(PScriptFile){
            PyRun_SimpleFile(PScriptFile, file_path.c_str());
            fclose(PScriptFile);
        }
    }
    catch (error_already_set)
    {
        PyErr_Print();
    }
};

void Demo (size_t dcm_number)
{
    CombinedHttpsClient dcm(
            g_program_path, "0.0.0.0", "443",
            g_program_path, "0.0.0.0", "4430");

    std::cout << dcm.Get("/dcap") << std::endl;
    std::cout << dcm.Get("/tm") << std::endl;
    std::cout << dcm.Get("/edev") << std::endl;
  
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
    std::cout << dcm.Post("/freq", freq) << std::endl;
    std::cout << dcm.Get("/fres") << std::endl;
    std::cout << dcm.Get("/sdev") << std::endl;
};

int main(int argc, char **argv) 
{
    if (argc < 2)
    {
        std::cout << "ERROR: must provide number of dcm to demo.\n";
        std::cout << "\tExample: ./dtm_testing 10\n";
        return 0;
    }

    wchar_t** wargv = new wchar_t*[argc];
    for(int i = 0; i < argc; i++)
    {
        wargv[i] = Py_DecodeLocale(argv[i], nullptr);
    }

    GetParentPath(argv);
    size_t client_count = atoi(argv[1]);
    
    std::string script_path = g_program_path + "/dtm_server.py";
    std::thread dtm(SpawnDTM, script_path, argc, wargv);
    std::this_thread::sleep_for (std::chrono::seconds(1));
    std::thread gsp(SpawnGSP);
    std::this_thread::sleep_for (std::chrono::seconds(1));

    // spawn all the dcm clients
    std::vector <std::thread> dcm_pool;
    dcm_pool.reserve(client_count);
    for (size_t i = 0; i < client_count; i++)
    {
        std::thread t(Demo, i+1);
        dcm_pool.emplace_back(std::move(t));
    } 

    // synchronize threads:
    for (auto &t : dcm_pool)
    {
        t.join();
    }

    dtm.detach();
    gsp.detach();
    return 0;
}
