#include <string>
#include <thread>
#include <fstream>
#include <gtest/gtest.h>
#include <https/https_server.hpp>
#include <https/https_client.hpp>
#include <xml/xml_validator.hpp>

extern std::string g_program_path;

class HttpsServerTests : public ::testing::Test 
{
protected:
    void SetUp() override 
    {        
        validator = new XmlValidator(g_program_path + "/sep_xml/sep.xsd");
        // read in the sample file
        std::ifstream ifs(g_program_path + "/sep_xml/DeviceCapability.xml");
        if (ifs)
        {
            std::ostringstream oss;
            oss << ifs.rdbuf();
            xml_str = oss.str();
            std::cout << "Validator: " << validator->ValidateXml(xml_str) << std::endl;        
        }
        else
        {
            std::cout << "couldn't open xml file" << std::endl;
        };
        https_server = new HttpsServer("0.0.0.0", 8080, g_program_path);
        first = new std::thread(&HttpsServer::Run, https_server);
    }

    void TearDown() override
    {
        https_server->Stop();
        first->join();
        delete https_server;
        delete validator;
    }

protected:
    HttpsServer* https_server;
    std::thread* first;
    XmlValidator *validator;
    std::string xml_str;
};

TEST_F(HttpsServerTests, GetDeviceCapability) 
{   
   HttpsClient *client = HttpsClient::getInstance(g_program_path,"0.0.0.0", "8080");
    try
    {
        auto resp = client->Get("/dcap");
        std::string msg = boost::beast::buffers_to_string(resp.body().data());
        std::cout << resp << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}
