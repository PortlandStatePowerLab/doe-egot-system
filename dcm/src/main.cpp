#include <iostream>
#include <string>
#include <sstream>
#include <https/https_client.hpp>
#include <sep/models.hpp>
#include <xml/adapter.hpp>
#include <xml/xml_validator.hpp>

std::string g_program_path;

void GetParentPath(char** arg)
{
    g_program_path = arg[0];
    std::size_t found = g_program_path.find_last_of("/\\");
    g_program_path = g_program_path.substr(0,found);
};


int main(int argc, char **argv)
{
  GetParentPath(argv);

  HttpsClient client(g_program_path, "localhost", "443");

  std::cout << client.Get("/dcap") << std::endl;
  std::cout << client.Get("/tm") << std::endl;
  std::cout << client.Get("/edev") << std::endl;
  
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
   client.Post("/freq", freq);
   std::cout << client.Get("/fres") << std::endl;
   std::cout << client.Get("/sdev") << std::endl;
    //std::cout << response << std::endl;
    //sep::DeviceCapability *dcap = new sep::DeviceCapability;
    //xml::Parse(boost::beast::buffers_to_string(response.body().data()), dcap);

    return 0;
}
