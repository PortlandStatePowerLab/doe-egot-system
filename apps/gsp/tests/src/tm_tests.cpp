#include <algorithm>
#include <fstream>
#include <gtest/gtest.h>
#include <https/client/single_client.hpp>
#include <https/server/server.hpp>
#include <sep/models/time.hpp>
#include <sep/wadl/wadl.hpp>
#include <sep/xml/adapter.hpp>
#include <sep/xml/xml_validator.hpp>
#include <string>
#include <thread>
#include <utilities/utilities.hpp>
#include <wadl_check.hpp>

extern std::string g_program_path;
using namespace https;

class HttpsTimeTests : public ::testing::Test {
protected:
  void SetUp() override {
    validator = new XmlValidator(g_program_path + "/sep_xml/sep.xsd");
  }

  void TearDown() override { delete validator; }

protected:
  XmlValidator *validator;
};

TEST_F(HttpsTimeTests, GetTime) {
  try {
    auto resp = SingleClient::getInstance().Get("/tm");
    std::string msg = boost::beast::buffers_to_string(resp.body().data());
    std::cout << msg << std::endl;

    EXPECT_TRUE(validator->ValidateXml(msg));

    sep::Time tm;
    xml::Parse(msg, &tm);
    EXPECT_TRUE(tm.href == "/tm");
  } catch (const std::exception &e) {
    ASSERT_ANY_THROW(e.what());
  }
}

TEST_F(HttpsTimeTests, PostTime) { EXPECT_TRUE(false); }

TEST_F(HttpsTimeTests, PutTime) { EXPECT_TRUE(false); }

TEST_F(HttpsTimeTests, DeleteTime) { EXPECT_TRUE(false); }