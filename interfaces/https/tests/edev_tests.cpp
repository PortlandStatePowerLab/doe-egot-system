#include <string>
#include <thread>
#include <fstream>
#include <gtest/gtest.h>
#include <https/https_server.hpp>
#include <https/https_client.hpp>
#include <xml/adapter.hpp>
#include <xml/xml_validator.hpp>
#include <ieee-2030.5/end_device.hpp>

extern std::string g_program_path;

class HttpsEndDeviceTests : public ::testing::Test
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

TEST_F(HttpsEndDeviceTests, GetEndDevice)
{
    HttpsClient *client1 = HttpsClient::getInstance("1", g_program_path, "0.0.0.0", "8080");
    try
    {
        auto resp = client1->Get("/edev");    
        std::string msg = boost::beast::buffers_to_string(resp.body().data());
        EXPECT_TRUE(validator->ValidateXml(msg));

        sep::EndDevice edev;
        xml::Parse(msg, &edev);
        EXPECT_TRUE(edev.href == "/edev");
        EXPECT_EQ(edev.lfdi,client1->getLFDI());
    }
    catch (const std::exception &e)
    {
        ASSERT_ANY_THROW(e.what());
    }

    try
    {
        auto resp = client1->Get("/edev");    
        std::string msg = boost::beast::buffers_to_string(resp.body().data());
    }
    catch (const std::exception &e)
    {
        ASSERT_ANY_THROW(e.what());
    }

    try
    {
        auto resp = client1->Get("/edev");    
        std::string msg = boost::beast::buffers_to_string(resp.body().data());
    }
    catch (const std::exception &e)
    {
        ASSERT_ANY_THROW(e.what());
    }
}

TEST_F(HttpsEndDeviceTests, PostEndDevice)
{
    EXPECT_TRUE(false);
}

TEST_F(HttpsEndDeviceTests, PutEndDevice)
{
    EXPECT_TRUE(false);
}

TEST_F(HttpsEndDeviceTests, DeleteEndDevice)
{
    EXPECT_TRUE(false);
}