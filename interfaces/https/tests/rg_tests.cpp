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

        // read in the sample file
        std::ifstream ifs(g_program_path + "/registration/6cd635a28e6f38dcd68c2681f2ab61a0fe1a6048/Registration.xml");
        if (ifs)
        {
            std::ostringstream oss;
            oss << ifs.rdbuf();
            xml_str = oss.str();
            xml::Parse(xml_str, &rg_control);
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
    sep::Registration rg_control;
};

TEST_F(HttpsRegistrationTests, GetRegistration)
{
    HttpsClient *client = HttpsClient::getInstance(g_program_path, "0.0.0.0", "8080");
    try
    {
        auto resp = client->Get("/rg");    
        std::string msg = boost::beast::buffers_to_string(resp.body().data());
        
        sep::Registration rg_test;
        xml::Parse(msg, &rg_test);
        EXPECT_TRUE(rg_control == rg_test);
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