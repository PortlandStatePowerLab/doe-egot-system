#include <algorithm>
#include <fstream>
#include <gtest/gtest.h>
#include <https/client/single_client.hpp>
#include <https/server/server.hpp>
#include <sep/models/flow_reservation_request.hpp>
#include <sep/wadl/wadl.hpp>
#include <sep/xml/adapter.hpp>
#include <sep/xml/xml_validator.hpp>
#include <string>
#include <thread>
#include <utilities/utilities.hpp>
#include <wadl_check.hpp>

extern std::string g_program_path;
using namespace https;

class HttpsFlowReservationRequestTests : public ::testing::Test {
protected:
  void SetUp() override {
    validator = new XmlValidator(g_program_path + "/sep_xml/sep.xsd");
  }

  void TearDown() override { delete validator; }

protected:
  XmlValidator *validator;
  std::string path = "/frq";
};

TEST_F(HttpsFlowReservationRequestTests, Get) {
  try {
    sep::FlowReservationRequest frq;
    frq.creation_time = psu::utilities::getTime();
    frq.description = "HttpsFlowReservationResponseListTests";
    frq.duration_requested.emplace(60 * 60);
    frq.energy_requested.value = 1000;
    frq.energy_requested.multiplier = 1;
    frq.power_requested.value = 1000;
    frq.power_requested.multiplier = 1;
    frq.href = path;
    frq.interval_requested.start = frq.creation_time;
    frq.interval_requested.duration = frq.duration_requested.value() * 3;
    frq.mrid = 0x9876;
    frq.request_status.datetime = frq.creation_time;
    frq.request_status.status = sep::RequestStatus::Status::kRequested;

    SingleClient::getInstance().Post(frq.href, xml::Serialize(frq));

    std::string uri = frq.href + "/" + xml::util::Hexify(frq.mrid);
    auto resp = SingleClient::getInstance().Get(uri);
    std::string msg = boost::beast::buffers_to_string(resp.body().data());
    xml::Parse(msg, &frq);

    std::string wadl_path = g_program_path + "/sep_xml/sep_wadl.xml";
    sep::WADLResource wadl_access =
        sep::WADL::getInstance(wadl_path)->getResource(path + "/*");

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

TEST_F(HttpsFlowReservationRequestTests, Post) {
  try {
    auto resp = SingleClient::getInstance().Get(path);
    std::string msg = boost::beast::buffers_to_string(resp.body().data());

    sep::FlowReservationRequestList frq_list;
    xml::Parse(msg, &frq_list);
    sep::FlowReservationRequest frq = frq_list.flow_reservation_requests[0];

    resp = SingleClient::getInstance().Post(frq.href, xml::Serialize(frq));

    std::string wadl_path = g_program_path + "/sep_xml/sep_wadl.xml";
    sep::WADLResource wadl_access =
        sep::WADL::getInstance(wadl_path)->getResource(path + "/*");

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

TEST_F(HttpsFlowReservationRequestTests, Put) {
  try {
    auto resp = SingleClient::getInstance().Get(path);
    std::string msg = boost::beast::buffers_to_string(resp.body().data());

    sep::FlowReservationRequestList frq_list;
    xml::Parse(msg, &frq_list);
    sep::FlowReservationRequest frq = frq_list.flow_reservation_requests[0];

    resp = SingleClient::getInstance().Put(frq.href, xml::Serialize(frq));

    std::string wadl_path = g_program_path + "/sep_xml/sep_wadl.xml";
    sep::WADLResource wadl_access =
        sep::WADL::getInstance(wadl_path)->getResource(path + "/*");

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

TEST_F(HttpsFlowReservationRequestTests, Delete) {
  try {
    std::string uri =
        path + "/" + xml::util::Hexify(SingleClient::getInstance().getLFDI());
    auto resp = SingleClient::getInstance().Delete(uri);

    std::string wadl_path = g_program_path + "/sep_xml/sep_wadl.xml";
    sep::WADLResource wadl_access =
        sep::WADL::getInstance(wadl_path)->getResource(path + "/*");

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