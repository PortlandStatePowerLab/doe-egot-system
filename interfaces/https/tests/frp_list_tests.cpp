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

class HttpsFlowReservationResponseListTests : public ::testing::Test
{
protected:
    void SetUp() override
    {
        HttpsClient *client1 = HttpsClient::getInstance("1", g_program_path, "0.0.0.0", "8080");

        frq.creation_time = psu::utilities::getTime();
        frq.description = "HttpsFlowReservationResponseListTests";
        frq.duration_requested = 60*60;
        frq.energy_requested.value = 1000;
        frq.energy_requested.multiplier = 1;
        frq.power_requested.value = 1000;
        frq.power_requested.multiplier = 1;
        frq.href = "/frq";
        frq.inherited_poll_rate = 900;
        frq.interval_requested.start = frq.creation_time;
        frq.interval_requested.duration = frq.duration_requested*3;
        frq.mrid = client1->getLFDI();
        frq.request_status.datetime = frq.creation_time;
        frq.request_status.status = sep::RequestStatus::Status::kRequested;

        client1->Post(frq.href, xml::Serialize(frq));

        validator = new XmlValidator(g_program_path + "/sep_xml/sep.xsd");
    }

    void TearDown() override
    {
        delete validator;
    }

protected:
    XmlValidator *validator;
    std::string path = "/frp";
    sep::FlowReservationRequest frq;
};

TEST_F(HttpsFlowReservationResponseListTests, GetResponseSet)
{
    HttpsClient *client1 = HttpsClient::getInstance("1", g_program_path, "0.0.0.0", "8080");
    try
    {
        auto resp = client1->Get(path);

        std::string msg = boost::beast::buffers_to_string(resp.body().data());

        std::cout << msg << "\n";

        std::vector<sep::FlowReservationResponse> frp_list;
        xml::Parse(msg, &frp_list);

        EXPECT_EQ(frp_list[0].mrid, client1->getLFDI());

        std::cout << "No EXPECT_EQ?\n";

        std::string wadl_path = g_program_path + "/sep_xml/sep_wadl.xml";
        sep::WADLResource wadl_access = sep::WADL::getInstance(wadl_path)->getResource(path);

        std::string method = "GET";

        std::cout << "Check Response" << "\n";
        // EXPECT_TRUE(checkContentType(resp.at("Content-Type").to_string(), wadl_access.properties[method].content_type));
        EXPECT_TRUE(checkStatus(resp.base().result_int(), wadl_access.properties[method].status));
        EXPECT_TRUE(checkParams(headerFields(resp), wadl_access.properties[method].params));
    }
    catch (const std::exception &e)
    {
        ASSERT_ANY_THROW(e.what());
    }
}

TEST_F(HttpsFlowReservationResponseListTests, PostResponseSet)
{
    HttpsClient *client1 = HttpsClient::getInstance("1", g_program_path, "0.0.0.0", "8080");
    try
    {
        auto resp = client1->Get(path);

        std::string msg = boost::beast::buffers_to_string(resp.body().data());

        std::vector<sep::FlowReservationResponse> frp_list;
        xml::Parse(msg, &frp_list);

        resp = client1->Post(path, xml::Serialize(frp_list[0]));

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

TEST_F(HttpsFlowReservationResponseListTests, PutResponseSet)
{
    HttpsClient *client1 = HttpsClient::getInstance("1", g_program_path, "0.0.0.0", "8080");
    try
    {
        auto resp = client1->Get(path);

        std::string msg = boost::beast::buffers_to_string(resp.body().data());

        std::vector<sep::FlowReservationResponse> frp_list;
        xml::Parse(msg, &frp_list);

        resp = client1->Put(path, xml::Serialize(frp_list[0]));

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

TEST_F(HttpsFlowReservationResponseListTests, DeleteResponseSet)
{
    HttpsClient *client1 = HttpsClient::getInstance("1", g_program_path, "0.0.0.0", "8080");
    try
    {
        auto resp = client1->Get(path);

        std::string msg = boost::beast::buffers_to_string(resp.body().data());

        std::vector<sep::FlowReservationResponse> frp_list;
        xml::Parse(msg, &frp_list);

        resp = client1->Delete(path);

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