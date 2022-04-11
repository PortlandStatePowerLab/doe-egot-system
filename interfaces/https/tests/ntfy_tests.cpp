#include <string>
#include <thread>
#include <fstream>
#include <gtest/gtest.h>
#include <https/https_server.hpp>
#include <https/https_client.hpp>
#include <xml/adapter.hpp>
#include <xml/xml_validator.hpp>

extern std::string g_program_path;

class HttpsNotificationTests : public ::testing::Test
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

TEST_F(HttpsNotificationTests, GetNotification)
{
    EXPECT_TRUE(false);
}

TEST_F(HttpsNotificationTests, PostNotification)
{
    EXPECT_TRUE(false);
}

TEST_F(HttpsNotificationTests, PutNotification)
{
    EXPECT_TRUE(false);
}

TEST_F(HttpsNotificationTests, DeleteNotification)
{
    EXPECT_TRUE(false);
}