#include <string>
#include <thread>
#include <fstream>
#include <gtest/gtest.h>
#include <https/https_server.hpp>
#include <https/https_client.hpp>
#include <xml/adapter.hpp>
#include <xml/xml_validator.hpp>
#include <ieee-2030.5/self_device.hpp>

extern std::string g_program_path;

class HttpsSelfDeviceTests : public ::testing::Test
{
protected:
    void SetUp() override
    {
        validator = new XmlValidator(g_program_path + "/sep_xml/sep.xsd");

        // read in the sample file
        std::ifstream ifs(g_program_path + "/sep_xml/SelfDevice.xml");
        if (ifs)
        {
            std::ostringstream oss;
            oss << ifs.rdbuf();
            xml_str = oss.str();
            xml::Parse(xml_str, &sdev_control);
        }
        else
        {
            std::cout << "couldn't open xml file" << std::endl;
        };
        ifs.close();
    }

    void TearDown() override
    {
        delete validator;
    }

protected:
    XmlValidator *validator;
    std::string xml_str;
    sep::SelfDevice sdev_control;
};

TEST_F(HttpsSelfDeviceTests, GetSelfDevice)
{
    HttpsClient *client = HttpsClient::getInstance(g_program_path, "0.0.0.0", "8080");
    try
    {
        auto resp = client->Get("/sdev");    
        std::string msg = boost::beast::buffers_to_string(resp.body().data());
        
        sep::SelfDevice sdev_test;
        xml::Parse(msg, &sdev_test);
        EXPECT_TRUE(sdev_control == sdev_test);
    }
    catch (const std::exception &e)
    {
        ASSERT_ANY_THROW(e.what());
    }
}

TEST_F(HttpsSelfDeviceTests, PostSelfDevice)
{
    EXPECT_TRUE(false);
}

TEST_F(HttpsSelfDeviceTests, PutSelfDevice)
{
    EXPECT_TRUE(false);
}

TEST_F(HttpsSelfDeviceTests, DeleteSelfDevice)
{
    EXPECT_TRUE(false);
}