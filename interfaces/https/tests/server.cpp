#include <string>
#include <thread>
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
    }

    void TearDown() override
    {
        delete validator;
    }

protected:
    XmlValidator *validator;
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

TEST_F(HttpsServerTests, GetDeviceCapability2) 
{   
   HttpsClient *client = HttpsClient::getInstance(g_program_path,"0.0.0.0", "8080");
    try
    {
        auto resp = client->Get("/dcap");
        std::string msg = boost::beast::buffers_to_string(resp.body().data());
        EXPECT_TRUE(validator->ValidateXml(msg));
        std::cout << "Validator : " << validator->ValidateXml(msg) << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}
