#include <string>
#include <thread>
#include <fstream>
#include <gtest/gtest.h>
#include <https/https_server.hpp>
#include <https/https_client.hpp>
#include <xml/adapter.hpp>
#include <xml/xml_validator.hpp>
#include <ieee-2030.5/device_capability.hpp>

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
            xml::Parse(xml_str, &dcap_control);
        }
        else
        {
            std::cout << "couldn't open xml file" << std::endl;
        };
    }

    void TearDown() override
    {
        delete validator;
    }

protected:
    XmlValidator *validator;
    std::string xml_str;
    sep::DeviceCapability dcap_control;
};

TEST_F(HttpsServerTests, GetDeviceCapability)
{
    HttpsClient *client = HttpsClient::getInstance(g_program_path, "0.0.0.0", "8080");
    try
    {
        auto resp = client->Get("/dcap");
        std::string msg = boost::beast::buffers_to_string(resp.body().data());

        sep::DeviceCapability dcap_test;
        xml::Parse(msg, &dcap_test);
        EXPECT_TRUE(dcap_control == dcap_test);
    }
    catch (const std::exception &e)
    {
        ASSERT_ANY_THROW(e.what());
    }
}

TEST_F(HttpsServerTests, PostDeviceCapability)
{
    EXPECT_TRUE(false);
}

TEST_F(HttpsServerTests, PutDeviceCapability)
{
    EXPECT_TRUE(false);
}

TEST_F(HttpsServerTests, DeleteDeviceCapability)
{
    EXPECT_TRUE(false);
}