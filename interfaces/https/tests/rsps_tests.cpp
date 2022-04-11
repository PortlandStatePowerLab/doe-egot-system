#include <string>
#include <thread>
#include <fstream>
#include <gtest/gtest.h>
#include <https/https_server.hpp>
#include <https/https_client.hpp>
#include <xml/adapter.hpp>
#include <xml/xml_validator.hpp>

extern std::string g_program_path;

class HttpsResponseSetTests : public ::testing::Test
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

TEST_F(HttpsResponseSetTests, GetResponseSet)
{
    EXPECT_TRUE(false);
}

TEST_F(HttpsResponseSetTests, PostResponseSet)
{
    EXPECT_TRUE(false);
}

TEST_F(HttpsResponseSetTests, PutResponseSet)
{
    EXPECT_TRUE(false);
}

TEST_F(HttpsResponseSetTests, DeleteResponseSet)
{
    EXPECT_TRUE(false);
}