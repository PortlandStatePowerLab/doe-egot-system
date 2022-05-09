#include <string>
#include <thread>
#include <fstream>
#include <gtest/gtest.h>
#include <https/https_server.hpp>
#include <https/https_client.hpp>
#include <xml/adapter.hpp>
#include <xml/xml_validator.hpp>
#include <utilities/utilities.hpp>
#include <wadl/wadl.hpp>
#include "wadl_check.hpp"

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
    std::string path = "/rsps";
};

TEST_F(HttpsResponseSetTests, GetResponseSet)
{
HttpsClient *client1 = HttpsClient::getInstance("1", g_program_path, "0.0.0.0", "8080");
    try
    {
            
        sep::Response rsp;
        rsp.href = "";
        rsp.end_device_lfdi = client1->getLFDI();
        rsp.status = sep::Response::Status::kEventAcknowledged;
        rsp.subject = 12345;
        rsp.created_date_time = psu::utilities::getTime();

        auto resp = client1->Post(path, xml::Serialize(rsp));
        
        std::string wadl_path = g_program_path + "/sep_xml/sep_wadl.xml";
        sep::WADLResource wadl_access = sep::WADL::getInstance(wadl_path)->getResource(path);
        
        std::string method = "POST";
        // EXPECT_TRUE(checkContentType(resp.at("Content-Type").to_string(), wadl_access.properties[method].content_type));
        EXPECT_TRUE(checkStatus(resp.base().result_int(), wadl_access.properties[method].status));
        EXPECT_TRUE(checkParams(headerFields(resp), wadl_access.properties[method].params));      
    }
    catch (const std::exception &e)
    {
        ASSERT_ANY_THROW(e.what());
    }
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