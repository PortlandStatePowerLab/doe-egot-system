#include <fstream>
#include <gtest/gtest.h>
#include <https/client/single_client.hpp>
#include <https/server/server.hpp>
#include <sep/models/end_device.hpp>
#include <sep/wadl/wadl.hpp>
#include <sep/xml/adapter.hpp>
#include <sep/xml/xml_validator.hpp>
#include <string>
#include <thread>
#include <utilities/utilities.hpp>
#include <wadl_check.hpp>

extern std::string g_program_path;
using namespace https;

class HttpsEndDeviceListTests : public ::testing::Test {
protected:
  void SetUp() override {
    validator = new XmlValidator(g_program_path + "/sep_xml/sep.xsd");
  }

  void TearDown() override { delete validator; }

protected:
  XmlValidator *validator;
  std::string path = "/edev";
};

TEST_F(HttpsEndDeviceListTests, GetEndDeviceList) {
  try {
    auto resp = SingleClient::getInstance().Get(path);
    std::string msg = boost::beast::buffers_to_string(resp.body().data());

    sep::EndDeviceList edev_list;
    xml::Parse(msg, &edev_list);

    EXPECT_EQ(edev_list.end_devices[0].lfdi,
              SingleClient::getInstance().getLFDI());

    std::string wadl_path = g_program_path + "/sep_xml/sep_wadl.xml";
    sep::WADLResource wadl_access =
        sep::WADL::getInstance(wadl_path)->getResource(path);

    std::string method = "GET";
    // EXPECT_TRUE(checkContentType(resp.at("Content-Type").to_string(),
    // wadl_access.properties[method].content_type));
    EXPECT_TRUE(checkStatus(resp.base().result_int(),
                            wadl_access.properties[method].status));
    EXPECT_TRUE(
        checkParams(headerFields(resp), wadl_access.properties[method].params));
  } catch (const std::exception &e) {
    ASSERT_ANY_THROW(e.what());
  }
}

TEST_F(HttpsEndDeviceListTests, PostEndDeviceList) {
  try {
    auto resp = SingleClient::getInstance().Get(path);
    std::string msg = boost::beast::buffers_to_string(resp.body().data());
    sep::EndDeviceList edev_list;
    xml::Parse(msg, &edev_list);

    resp = SingleClient::getInstance().Post(
        path, xml::Serialize(edev_list.end_devices[0]));

    std::string wadl_path = g_program_path + "/sep_xml/sep_wadl.xml";
    sep::WADLResource wadl_access =
        sep::WADL::getInstance(wadl_path)->getResource(path);

    std::string method = "POST";
    // EXPECT_TRUE(checkContentType(resp.at("Content-Type").to_string(),
    // wadl_access.properties[method].content_type));
    EXPECT_TRUE(checkStatus(resp.base().result_int(),
                            wadl_access.properties[method].status));
    EXPECT_TRUE(
        checkParams(headerFields(resp), wadl_access.properties[method].params));
  } catch (const std::exception &e) {
    ASSERT_ANY_THROW(e.what());
  }
}

TEST_F(HttpsEndDeviceListTests, PutEndDeviceList) {
  try {
    auto resp = SingleClient::getInstance().Get(path);
    std::string msg = boost::beast::buffers_to_string(resp.body().data());

    sep::EndDeviceList edev_list;
    xml::Parse(msg, &edev_list);

    resp = SingleClient::getInstance().Put(
        path, xml::Serialize(edev_list.end_devices[0]));

    std::string wadl_path = g_program_path + "/sep_xml/sep_wadl.xml";
    sep::WADLResource wadl_access =
        sep::WADL::getInstance(wadl_path)->getResource(path);

    std::string method = "PUT";
    // EXPECT_TRUE(checkContentType(resp.at("Content-Type").to_string(),
    // wadl_access.properties[method].content_type));
    EXPECT_TRUE(checkStatus(resp.base().result_int(),
                            wadl_access.properties[method].status));
    EXPECT_TRUE(
        checkParams(headerFields(resp), wadl_access.properties[method].params));
  } catch (const std::exception &e) {
    ASSERT_ANY_THROW(e.what());
  }
}

TEST_F(HttpsEndDeviceListTests, DeleteEndDeviceList) {
  try {
    auto resp = SingleClient::getInstance().Get(path);
    std::string msg = boost::beast::buffers_to_string(resp.body().data());

    sep::EndDeviceList edev_list;
    xml::Parse(msg, &edev_list);

    resp = SingleClient::getInstance().Delete(path);

    std::string wadl_path = g_program_path + "/sep_xml/sep_wadl.xml";
    sep::WADLResource wadl_access =
        sep::WADL::getInstance(wadl_path)->getResource(path);

    std::string method = "DELETE";
    // EXPECT_TRUE(checkContentType(resp.at("Content-Type").to_string(),
    // wadl_access.properties[method].content_type));
    EXPECT_TRUE(checkStatus(resp.base().result_int(),
                            wadl_access.properties[method].status));
    EXPECT_TRUE(
        checkParams(headerFields(resp), wadl_access.properties[method].params));
  } catch (const std::exception &e) {
    ASSERT_ANY_THROW(e.what());
  }
}