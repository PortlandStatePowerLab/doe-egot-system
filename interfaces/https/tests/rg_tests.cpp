#include <string>
#include <thread>
#include <fstream>
#include <gtest/gtest.h>
#include <https/https_server.hpp>
#include <https/https_client.hpp>
#include <xml/adapter.hpp>
#include <xml/xml_validator.hpp>
#include <ieee-2030.5/registration.hpp>

extern std::string g_program_path;

class HttpsRegistrationTests : public ::testing::Test
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

TEST_F(HttpsRegistrationTests, GetRegistration)
{
    HttpsClient *client1 = HttpsClient::getInstance("1", g_program_path, "0.0.0.0", "8080");
    try
    {
        auto resp = client1->Get("/rg");    
        std::string msg = boost::beast::buffers_to_string(resp.body().data());
        EXPECT_TRUE(validator->ValidateXml(msg));

        sep::Registration rg;
        xml::Parse(msg, &rg);
        EXPECT_TRUE(rg.href == "/rg");
        EXPECT_EQ(rg.pin, xml::util::generatePIN(xml::util::Hexify(client1->getLFDI())));
    }
    catch (const std::exception &e)
    {
        ASSERT_ANY_THROW(e.what());
    }
}

TEST_F(HttpsRegistrationTests, PostRegistration)
{
    EXPECT_TRUE(false);
}

TEST_F(HttpsRegistrationTests, PutRegistration)
{
    EXPECT_TRUE(false);
}

TEST_F(HttpsRegistrationTests, DeleteRegistration)
{
    EXPECT_TRUE(false);
}