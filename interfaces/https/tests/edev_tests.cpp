#include <string>
#include <thread>
#include <fstream>
#include <gtest/gtest.h>
#include <https/https_server.hpp>
#include <https/https_client.hpp>
#include <xml/adapter.hpp>
#include <xml/xml_validator.hpp>
#include <wadl/wadl.hpp>
#include <ieee-2030.5/end_device.hpp>
#include "wadl_check.hpp"

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
    std::string path = "/edev";
};

TEST_F(HttpsEndDeviceTests, GetEndDevice)
{
    HttpsClient *client1 = HttpsClient::getInstance("1", g_program_path, "0.0.0.0", "8080");
    try
    {
        std::string uri = path + "/" + xml::util::Hexify(client1->getLFDI());
        auto resp = client1->Get(uri);

        std::string msg = boost::beast::buffers_to_string(resp.body().data());

        sep::EndDevice edev;
        xml::Parse(msg, &edev);

        std::string wadl_path = g_program_path + "/sep_xml/sep_wadl.xml";
        sep::WADLResource wadl_access = sep::WADL::getInstance(wadl_path)->getResource(path+"/*");

        std::string method = "GET";
        // EXPECT_TRUE(checkContentType(resp.at("Content-Type").to_string(), wadl_access.properties[method].content_type));
        EXPECT_TRUE(checkStatus(resp.base().result_int(), wadl_access.properties[method].status));
        EXPECT_TRUE(checkParams(headerFields(resp), wadl_access.properties[method].params));
    }
    catch (const std::exception &e)
    {
        ASSERT_ANY_THROW(e.what());
    }
}

TEST_F(HttpsEndDeviceTests, PostEndDevice)
{
    HttpsClient *client1 = HttpsClient::getInstance("1", g_program_path, "0.0.0.0", "8080");
    try
    {
        std::string uri = path + "/" + xml::util::Hexify(client1->getLFDI());
        auto resp = client1->Get(uri);

        std::string msg = boost::beast::buffers_to_string(resp.body().data());

        sep::EndDevice edev;
        xml::Parse(msg, &edev);

        resp = client1->Post(uri, xml::Serialize(edev));

        std::string wadl_path = g_program_path + "/sep_xml/sep_wadl.xml";
        sep::WADLResource wadl_access = sep::WADL::getInstance(wadl_path)->getResource(path+"/*");

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

TEST_F(HttpsEndDeviceTests, PutEndDevice)
{
    HttpsClient *client1 = HttpsClient::getInstance("1", g_program_path, "0.0.0.0", "8080");
    try
    {
        std::string uri = path + "/" + xml::util::Hexify(client1->getLFDI());
        auto resp = client1->Get(uri);

        std::string msg = boost::beast::buffers_to_string(resp.body().data());

        sep::EndDevice edev;
        xml::Parse(msg, &edev);

        resp = client1->Put(uri, xml::Serialize(edev));

        std::string wadl_path = g_program_path + "/sep_xml/sep_wadl.xml";
        sep::WADLResource wadl_access = sep::WADL::getInstance(wadl_path)->getResource(path+"/*");

        std::string method = "PUT";
        // EXPECT_TRUE(checkContentType(resp.at("Content-Type").to_string(), wadl_access.properties[method].content_type));
        EXPECT_TRUE(checkStatus(resp.base().result_int(), wadl_access.properties[method].status));
        EXPECT_TRUE(checkParams(headerFields(resp), wadl_access.properties[method].params));
    }
    catch (const std::exception &e)
    {
        ASSERT_ANY_THROW(e.what());
    }
}

TEST_F(HttpsEndDeviceTests, DeleteEndDevice)
{
    HttpsClient *client1 = HttpsClient::getInstance("1", g_program_path, "0.0.0.0", "8080");
    try
    {
        std::string uri = path + "/" + xml::util::Hexify(client1->getLFDI());
        auto resp = client1->Delete(uri);

        std::string wadl_path = g_program_path + "/sep_xml/sep_wadl.xml";
        sep::WADLResource wadl_access = sep::WADL::getInstance(wadl_path)->getResource(path+"/*");

        std::string method = "DELETE";
        // EXPECT_TRUE(checkContentType(resp.at("Content-Type").to_string(), wadl_access.properties[method].content_type));
        EXPECT_TRUE(checkStatus(resp.base().result_int(), wadl_access.properties[method].status));
        EXPECT_TRUE(checkParams(headerFields(resp), wadl_access.properties[method].params));
    }
    catch (const std::exception &e)
    {
        ASSERT_ANY_THROW(e.what());
    }
}