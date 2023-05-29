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

class HttpsFlowReservationRequestListTests : public ::testing::Test
{
protected:
    void SetUp() override
    {
        frq.creation_time = psu::utilities::getTime();
        frq.description = "HttpsFlowReservationResponseListTests";
        frq.duration_requested = 60*60;
        frq.energy_requested.value = 1000;
        frq.energy_requested.multiplier = 1;
        frq.power_requested.value = 1000;
        frq.power_requested.multiplier = 1;
        frq.href = "/frq";
        frq.interval_requested.start = frq.creation_time;
        frq.interval_requested.duration = frq.duration_requested*3;
        frq.mrid = 0x9999;
        frq.request_status.datetime = frq.creation_time;
        frq.request_status.status = sep::RequestStatus::Status::kRequested;

        SingleClient::getInstance().Post(frq.href, xml::Serialize(frq));

        validator = new XmlValidator(g_program_path + "/sep_xml/sep.xsd");
    }

    void TearDown() override
    {
        delete validator;
    }

protected:
    XmlValidator *validator;
    std::string path = "/frq";
    sep::FlowReservationRequest frq;
};

TEST_F(HttpsFlowReservationRequestListTests, GetList)
{
    try
    {
        auto resp = SingleClient::getInstance().Get(path);

        std::string msg = boost::beast::buffers_to_string(resp.body().data());

        sep::FlowReservationRequestList frq_list;
        xml::Parse(msg, &frq_list);

        EXPECT_EQ(frq_list.flow_reservation_requests[0].mrid, frq.mrid);

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

TEST_F(HttpsFlowReservationRequestListTests, PostList)
{
    try
    {
        auto resp = SingleClient::getInstance().Get(path);

        std::string msg = boost::beast::buffers_to_string(resp.body().data());

        sep::FlowReservationRequestList frq_list;
        xml::Parse(msg, &frq_list);

        resp = SingleClient::getInstance().Post(path, xml::Serialize(frq_list.flow_reservation_requests[0]));

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

TEST_F(HttpsFlowReservationRequestListTests, PutList)
{
    try
    {
        auto resp = SingleClient::getInstance().Get(path);

        std::string msg = boost::beast::buffers_to_string(resp.body().data());

        sep::FlowReservationRequestList frq_list;
        xml::Parse(msg, &frq_list);

        resp = SingleClient::getInstance().Put(path, xml::Serialize(frq_list.flow_reservation_requests[0]));

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

TEST_F(HttpsFlowReservationRequestListTests, DeleteList)
{
    try
    {
        auto resp = SingleClient::getInstance().Get(path);

        std::string msg = boost::beast::buffers_to_string(resp.body().data());

        sep::FlowReservationRequestList frq_list;
        xml::Parse(msg, &frq_list);

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