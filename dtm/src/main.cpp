#include <boost/python.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <iostream>
#include <stdlib.h>
#include <thread>         // std::thread
#include <string>
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
    pt->put("DCM.cert", "/root-ca/certs/client1.crt");
    std::cout << pt->get<int>("DTM.port") << std::endl;
    std::cout << pt->get<std::string>("DCM.cert") << std::endl;
};

void SpawnDTM(int argc, char **argv)
{
    DistributedTrustManagment dtm(argc, argv);
};

int main(int argc, char **argv)
{
    std::string config = GetParentPath(argv) + "/../../config.ini";

    // Create empty property tree object
    boost::property_tree::ptree pt;
    boost::property_tree::read_ini(config, pt);

    ResetConfig(&pt);
    boost::property_tree::write_ini(config, pt);
    std::thread T1 (SpawnDTM, argc, argv);
    
    // synchronize threads:
    T1.join(); 
}
