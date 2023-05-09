#include "include/dtm/dtm_server.hpp"
#include <boost/python.hpp>
#include <utilities/utilities.hpp>
#include <string>
#include <iostream>

using namespace boost::python;

DistributedTrustManagment::DistributedTrustManagment(int argc, char **argv)
{
    std::string root = psu::utilities::getProgramPath(argv);
    wchar_t** wargv = new wchar_t*[argc];
    for(int i = 0; i < argc; i++)
    {
        wargv[i] = Py_DecodeLocale(root.c_str(), nullptr);
    }

    try
    {
        std::string script_path = root + "/scripts/simple_server.py";
        Py_Initialize();
        PySys_SetArgv(argc, wargv);
        FILE* PScriptFile = fopen(script_path.c_str(), "r");
        if(PScriptFile){
            PyRun_SimpleFile(PScriptFile, script_path.c_str());
            fclose(PScriptFile);
        }
        std::cout << "[PyScript] Error opening file: " << script_path << std::endl;
    }
    catch (error_already_set)
    {
        PyErr_Print();
    }
}

DistributedTrustManagment::~DistributedTrustManagment() 
{
    // do nothing
}