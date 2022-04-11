#include <string>
#include <thread>
#include <fstream>
#include <gtest/gtest.h>
#include <https/https_server.hpp>
#include <https/https_client.hpp>
#include <xml/adapter.hpp>
#include <xml/xml_validator.hpp>
#include <ieee-2030.5/time.hpp>

extern std::string g_program_path;

class HttpsTimeTests : public ::testing::Test
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

TEST_F(HttpsTimeTests, GetTime)
{
    HttpsClient* client1 = HttpsClient::getInstance("1", g_program_path, "0.0.0.0", "8080");
    try
    {
        auto resp = client1->Get("/tm");
        std::string msg = boost::beast::buffers_to_string(resp.body().data());
        EXPECT_TRUE(validator->ValidateXml(msg));

        sep::Time tm;
        xml::Parse(msg, &tm);
        EXPECT_TRUE(tm.href == "/tm");      
    }
    catch (const std::exception &e)
    {
        ASSERT_ANY_THROW(e.what());
    }
}

TEST_F(HttpsTimeTests, PostTime)
{
    EXPECT_TRUE(false);
}

TEST_F(HttpsTimeTests, PutTime)
{
    EXPECT_TRUE(false);
}

TEST_F(HttpsTimeTests, DeleteTime)
{
    EXPECT_TRUE(false);
}