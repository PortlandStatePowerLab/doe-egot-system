#include <string>
#include <thread>
#include <fstream>
#include <gtest/gtest.h>
#include <https/https_server.hpp>
#include <https/single_client.hpp>
#include <xml/adapter.hpp>
#include <xml/xml_validator.hpp>
#include <utilities/utilities.hpp>
#include <wadl/wadl.hpp>
#include "wadl_check.hpp"

extern std::string g_program_path;
using namespace https;

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
    try
    {
        std::string uri = path + "/" + xml::util::Hexify(SingleClient::getInstance().getLFDI());
        auto resp = SingleClient::getInstance().Get(uri);

        std::string msg = boost::beast::buffers_to_string(resp.body().data());

        sep::ResponseSet rsps;
        xml::Parse(msg, &rsps);

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

TEST_F(HttpsResponseSetTests, PostResponseSet)
{
    try
    {
        std::string uri = path + "/" + xml::util::Hexify(SingleClient::getInstance().getLFDI());
        auto resp = SingleClient::getInstance().Get(uri);

        std::string msg = boost::beast::buffers_to_string(resp.body().data());

        sep::ResponseSet rsps;
        xml::Parse(msg, &rsps);

        resp = SingleClient::getInstance().Post(uri, xml::Serialize(rsps));

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

TEST_F(HttpsResponseSetTests, PutResponseSet)
{
    try
    {
        std::string uri = path + "/" + xml::util::Hexify(SingleClient::getInstance().getLFDI());
        auto resp = SingleClient::getInstance().Get(uri);

        std::string msg = boost::beast::buffers_to_string(resp.body().data());

        sep::ResponseSet rsps;
        xml::Parse(msg, &rsps);

        resp = SingleClient::getInstance().Put(uri, xml::Serialize(rsps));

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

TEST_F(HttpsResponseSetTests, DeleteResponseSet)
{
    try
    {
        std::string uri = path + "/" + xml::util::Hexify(SingleClient::getInstance().getLFDI());
        auto resp = SingleClient::getInstance().Delete(uri);

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