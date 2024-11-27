#include <string>
#include <thread>
#include <fstream>
#include <gtest/gtest.h>
#include <https/https_server.hpp>
#include <https/single_client.hpp>
#include <xml/adapter.hpp>
#include <xml/xml_validator.hpp>

extern std::string g_program_path;

class HttpsDeviceStatusTests : public ::testing::Test
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

TEST_F(HttpsDeviceStatusTests, GetDeviceStatus)
{
    EXPECT_TRUE(false);
}

TEST_F(HttpsDeviceStatusTests, PostDeviceStatus)
{
    EXPECT_TRUE(false);
}

TEST_F(HttpsDeviceStatusTests, PutDeviceStatus)
{
    EXPECT_TRUE(false);
}

TEST_F(HttpsDeviceStatusTests, DeleteDeviceStatus)
{
    EXPECT_TRUE(false);
}