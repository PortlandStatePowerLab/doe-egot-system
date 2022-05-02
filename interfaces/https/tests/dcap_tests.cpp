#include <string>
#include <thread>
#include <fstream>
#include <gtest/gtest.h>
#include <https/https_server.hpp>
#include <https/https_client.hpp>
#include <xml/adapter.hpp>
#include <xml/xml_validator.hpp>
#include <utilities/utilities.hpp>
#include <ieee-2030.5/device_capability.hpp>

extern std::string g_program_path;

class HttpsDeviceCapabilityTests : public ::testing::Test
{
protected:
    void SetUp() override
    {
        validator = new XmlValidator(g_program_path + "/sep_xml/sep.xsd");
        std::string wadl_file = psu::utilities::readFile(g_program_path + "/sep_xml/sep_wadl.xml");
        wadl = xml::util::Treeify(wadl_file);
    }

    void TearDown() override
    {
        delete validator;
    }

protected:
    XmlValidator *validator;
    boost::property_tree::ptree wadl;
};

TEST_F(HttpsDeviceCapabilityTests, GetDeviceCapability)
{
    HttpsClient *client = HttpsClient::getInstance("1", g_program_path, "0.0.0.0", "8080");
    try
    {
        auto resp = client->Get("/dcap");
        std::string msg = boost::beast::buffers_to_string(resp.body().data());
        EXPECT_TRUE(validator->ValidateXml(msg));

        sep::DeviceCapability dcap;
        xml::Parse(msg, &dcap);
        EXPECT_TRUE(dcap.href == "/dcap");  
    }
    catch (const std::exception &e)
    {
        ASSERT_ANY_THROW(e.what());
    }
}

TEST_F(HttpsDeviceCapabilityTests, PostDeviceCapability)
{
    EXPECT_TRUE(false);
}

TEST_F(HttpsDeviceCapabilityTests, PutDeviceCapability)
{
    EXPECT_TRUE(false);
}

TEST_F(HttpsDeviceCapabilityTests, DeleteDeviceCapability)
{
    EXPECT_TRUE(false);
}