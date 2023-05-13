#include <string>
#include <thread>
#include <fstream>
#include <algorithm>
#include <gtest/gtest.h>
#include <https/server/server.hpp>
#include <https/client/single_client.hpp>
#include <sep/xml/adapter.hpp>
#include <sep/xml/xml_validator.hpp>
#include <sep/wadl/wadl.hpp>
#include <utilities/utilities.hpp>
#include <sep/models/device_capability.hpp>
#include <wadl_check.hpp>

extern std::string g_program_path;
using namespace https;

class HttpsDeviceCapabilityTests : public ::testing::Test
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
    std::string path = "/dcap";
};

TEST_F(HttpsDeviceCapabilityTests, GetDeviceCapability)
{
    try
    {
        auto resp = SingleClient::getInstance().Get(path);
        std::string msg = boost::beast::buffers_to_string(resp.body().data());
        std::cout << msg << std::endl;
        
        sep::DeviceCapability dcap;
        xml::Parse(msg, &dcap);

        std::string wadl_path = g_program_path + "/sep_xml/sep_wadl.xml";
        sep::WADLResource wadl_access = sep::WADL::getInstance(wadl_path)->getResource(path);

        std::string method = "GET";
        EXPECT_TRUE(checkContentType(resp.at("Content-Type").to_string(), wadl_access.properties[method].content_type));
        EXPECT_TRUE(checkStatus(resp.base().result_int(), wadl_access.properties[method].status));
        EXPECT_TRUE(checkParams(headerFields(resp), wadl_access.properties[method].params));
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
}

TEST_F(HttpsDeviceCapabilityTests, PostDeviceCapability)
{
    try
    {
        auto resp = SingleClient::getInstance().Get(path);
        std::string msg = boost::beast::buffers_to_string(resp.body().data());

        sep::DeviceCapability dcap;
        xml::Parse(msg, &dcap);
        
        resp = SingleClient::getInstance().Post(path, xml::Serialize(dcap));

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

TEST_F(HttpsDeviceCapabilityTests, PutDeviceCapability)
{
    try
    {
        auto resp = SingleClient::getInstance().Get(path);
        std::string msg = boost::beast::buffers_to_string(resp.body().data());

        sep::DeviceCapability dcap;
        xml::Parse(msg, &dcap);

        resp = SingleClient::getInstance().Put(path, xml::Serialize(dcap));

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

TEST_F(HttpsDeviceCapabilityTests, DeleteDeviceCapability)
{
    try
    {       
        auto resp = SingleClient::getInstance().Delete("/dcap");

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