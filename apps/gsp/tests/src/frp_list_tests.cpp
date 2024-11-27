#include <algorithm>
#include <fstream>
#include <gtest/gtest.h>
#include <https/client/single_client.hpp>
#include <https/server/server.hpp>
#include <sep/models/flow_reservation_request.hpp>
#include <sep/models/flow_reservation_response.hpp>
#include <sep/wadl/wadl.hpp>
#include <sep/xml/adapter.hpp>
#include <sep/xml/xml_validator.hpp>
#include <string>
#include <thread>
#include <utilities/utilities.hpp>
#include <wadl_check.hpp>

extern std::string g_program_path;
using namespace https;

class HttpsFlowReservationResponseListTests : public ::testing::Test {
protected:
  void SetUp() override {
    frq.creation_time = psu::utilities::getTime();
    frq.description = "HttpsFlowReservationResponseListTests";
    frq.duration_requested = 60 * 60;
    frq.energy_requested.value = 1000;
    frq.energy_requested.multiplier = 1;
    frq.power_requested.value = 1000;
    frq.power_requested.multiplier = 1;
    frq.href = request_path;
    frq.interval_requested.start = frq.creation_time;
    if (frq.duration_requested.is_initialized()) {
      frq.interval_requested.duration = frq.duration_requested.value() * 3;
    }
    frq.mrid = mrid;
    frq.request_status.datetime = frq.creation_time;
    frq.request_status.status = sep::RequestStatus::Status::kRequested;

    SingleClient::getInstance().Post(frq.href, xml::Serialize(frq));

    validator = new XmlValidator(g_program_path + "/sep_xml/sep.xsd");
  }

  void TearDown() override { delete validator; }

protected:
  XmlValidator *validator;
  sep::FlowReservationRequest frq;
  std::string request_path = "/frq";
  std::string response_path = "/frp";
  sep::mRIDType mrid = 0x4321;
  std::string frq_uri = request_path + "/" + xml::util::Hexify(mrid);
  std::string frp_uri = response_path + "/" + xml::util::Hexify(mrid);
};

TEST_F(HttpsFlowReservationResponseListTests, GetList) {
  try {
    auto resp = SingleClient::getInstance().Get(response_path);
    std::string msg = boost::beast::buffers_to_string(resp.body().data());
    sep::FlowReservationResponseList frp_list;
    xml::Parse(msg, &frp_list);

    bool exists = false;
    for (auto &frp : frp_list.flow_reservation_responses) {
      if (frp.mrid == mrid) {
        exists = true;
      }
    }
    EXPECT_TRUE(exists);

    std::string wadl_path = g_program_path + "/sep_xml/sep_wadl.xml";
    sep::WADLResource wadl_access =
        sep::WADL::getInstance(wadl_path)->getResource(response_path);

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

TEST_F(HttpsFlowReservationResponseListTests, PostList) {
  try {
    auto resp = SingleClient::getInstance().Get(response_path);
    std::string msg = boost::beast::buffers_to_string(resp.body().data());

    sep::FlowReservationResponseList frp_list;
    xml::Parse(msg, &frp_list);

    resp = SingleClient::getInstance().Post(
        frp_list.flow_reservation_responses[0].href,
        xml::Serialize(frp_list.flow_reservation_responses[0]));

    std::string wadl_path = g_program_path + "/sep_xml/sep_wadl.xml";
    sep::WADLResource wadl_access =
        sep::WADL::getInstance(wadl_path)->getResource(response_path);

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

TEST_F(HttpsFlowReservationResponseListTests, PutList) {
  try {
    auto resp = SingleClient::getInstance().Get(response_path);
    std::string msg = boost::beast::buffers_to_string(resp.body().data());

    sep::FlowReservationResponseList frp_list;
    xml::Parse(msg, &frp_list);

    resp = SingleClient::getInstance().Put(
        frp_list.flow_reservation_responses[0].href,
        xml::Serialize(frp_list.flow_reservation_responses[0]));

    std::string wadl_path = g_program_path + "/sep_xml/sep_wadl.xml";
    sep::WADLResource wadl_access =
        sep::WADL::getInstance(wadl_path)->getResource(response_path);

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

TEST_F(HttpsFlowReservationResponseListTests, DeleteList) {
  try {
    auto resp = SingleClient::getInstance().Get(response_path);
    std::string msg = boost::beast::buffers_to_string(resp.body().data());

    sep::FlowReservationResponseList frp_list;
    xml::Parse(msg, &frp_list);

    resp = SingleClient::getInstance().Delete(
        frp_list.flow_reservation_responses[0].href);

    std::string wadl_path = g_program_path + "/sep_xml/sep_wadl.xml";
    sep::WADLResource wadl_access =
        sep::WADL::getInstance(wadl_path)->getResource(response_path);

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