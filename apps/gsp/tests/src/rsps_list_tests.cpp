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

class HttpsResponseSetListTests : public ::testing::Test
{
protected:
    void SetUp() override
    {
        rsps.description = "HttpsResponseSetListTests";
        rsps.href = path;
        rsps.inherited_poll_rate = 900;
        rsps.mrid = 0x9999;
        rsps.response_list_link;

        validator = new XmlValidator(g_program_path + "/sep_xml/sep.xsd");
    }

    void TearDown() override
    {
        delete validator;
    }

protected:
    XmlValidator *validator;
    std::string path = "/rsps";
    sep::ResponseSet rsps;
};

TEST_F(HttpsResponseSetListTests, GetResponseSet)
{
    try
    {
        auto resp = SingleClient::getInstance().Get(path);

        std::string msg = boost::beast::buffers_to_string(resp.body().data());

        std::vector<sep::ResponseSet> rsps_list;
        xml::Parse(msg, &rsps_list);

        EXPECT_EQ(rsps_list[0].mrid, SingleClient::getInstance().getLFDI());

        std::string wadl_path = g_program_path + "/sep_xml/sep_wadl.xml";
        sep::WADLResource wadl_access = sep::WADL::getInstance(wadl_path)->getResource(path);

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

TEST_F(HttpsResponseSetListTests, PostResponseSet)
{
    try
    {
        auto resp = SingleClient::getInstance().Get(path);

        std::string msg = boost::beast::buffers_to_string(resp.body().data());

        std::vector<sep::ResponseSet> rsps_list;
        xml::Parse(msg, &rsps_list);

        resp = SingleClient::getInstance().Post(path, xml::Serialize(rsps_list[0]));

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

TEST_F(HttpsResponseSetListTests, PutResponseSet)
{
    try
    {
        auto resp = SingleClient::getInstance().Get(path);

        std::string msg = boost::beast::buffers_to_string(resp.body().data());

        std::vector<sep::ResponseSet> rsps_list;
        xml::Parse(msg, &rsps_list);

        resp = SingleClient::getInstance().Put(path, xml::Serialize(rsps_list[0]));

        std::string wadl_path = g_program_path + "/sep_xml/sep_wadl.xml";
        sep::WADLResource wadl_access = sep::WADL::getInstance(wadl_path)->getResource(path);

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

TEST_F(HttpsResponseSetListTests, DeleteResponseSet)
{
    try
    {
        auto resp = SingleClient::getInstance().Get(path);

        std::string msg = boost::beast::buffers_to_string(resp.body().data());

        std::vector<sep::ResponseSet> rsps_list;
        xml::Parse(msg, &rsps_list);

        resp = SingleClient::getInstance().Delete(path);

        std::string wadl_path = g_program_path + "/sep_xml/sep_wadl.xml";
        sep::WADLResource wadl_access = sep::WADL::getInstance(wadl_path)->getResource(path);

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