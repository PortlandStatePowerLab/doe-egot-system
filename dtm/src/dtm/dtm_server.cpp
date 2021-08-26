#include "include/dtm/dtm_server.hpp"
#include <boost/python.hpp>
#include <string>

using namespace boost::python;

inline std::string GetParentPath(char** arg)
{
    std::string path = arg[0];
    std::size_t found = path.find_last_of("/\\");
    return path.substr(0,found);
}

DistributedTrustManagment::DistributedTrustManagment(int argc, char **argv)
{

    wchar_t** wargv = new wchar_t*[argc];
    for(int i = 0; i < argc; i++)
    {
        wargv[i] = Py_DecodeLocale(argv[i], nullptr);
    }

    try
    {
        Py_Initialize();
        PySys_SetArgv(argc, wargv);

        std::string script_path = GetParentPath(argv) + "/../../scripts/dtm_server.py";
        FILE* PScriptFile = fopen(script_path.c_str(), "r");
        if(PScriptFile){
            PyRun_SimpleFile(PScriptFile, script_path.c_str());
            fclose(PScriptFile);
        }
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