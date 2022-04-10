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
    }

    void TearDown() override
    {
        delete validator;
    }

protected:
    XmlValidator *validator;
};

TEST_F(HttpsSelfDeviceTests, GetSelfDevice)
{
    HttpsClient *client1 = HttpsClient::getInstance("1", g_program_path, "0.0.0.0", "8080");
    try
    {
        auto resp = client1->Get("/sdev");  
        std::string msg = boost::beast::buffers_to_string(resp.body().data());
        EXPECT_TRUE(validator->ValidateXml(msg));

        sep::SelfDevice sdev;
        xml::Parse(msg, &sdev);
        EXPECT_TRUE(sdev.href == "/sdev");
        EXPECT_EQ(sdev.lfdi,client1->getLFDI());
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