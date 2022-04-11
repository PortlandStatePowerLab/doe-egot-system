#include <string>
#include <thread>
#include <fstream>
#include <gtest/gtest.h>
#include <https/https_server.hpp>
#include <https/https_client.hpp>
#include <xml/adapter.hpp>
#include <xml/xml_validator.hpp>
#include <ieee-2030.5/response.hpp>

extern std::string g_program_path;

class HttpsResponseTests : public ::testing::Test
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

TEST_F(HttpsResponseTests, PostResponse)
{
    sep::Response rsp;
    EXPECT_TRUE(false);
}

TEST_F(HttpsResponseTests, GetResponse)
{
    EXPECT_TRUE(false);
}

TEST_F(HttpsResponseTests, PutResponse)
{
    EXPECT_TRUE(false);
}

TEST_F(HttpsResponseTests, DeleteResponse)
{
    EXPECT_TRUE(false);
}