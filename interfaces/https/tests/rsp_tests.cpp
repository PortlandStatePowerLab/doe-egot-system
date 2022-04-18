#include <string>
#include <thread>
#include <fstream>
#include <gtest/gtest.h>
#include <https/https_server.hpp>
#include <https/https_client.hpp>
#include <xml/adapter.hpp>
#include <xml/xml_validator.hpp>
#include <ieee-2030.5/response.hpp>
#include <utilities/utilities.hpp>

extern std::string g_program_path;

class HttpsResponseTests : public ::testing::Test
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
};

TEST_F(HttpsResponseTests, PostResponse)
{
    sep::Response rsp;
    rsp.href = "/rsp";
    rsp.end_device_lfdi = 123456789;
    rsp.status = sep::Response::Status::kEventAcknowledged;
    rsp.subject = 12345;
    rsp.created_date_time = psu::utilities::getTime();

    HttpsClient *client1 = HttpsClient::getInstance("1", g_program_path, "0.0.0.0", "8080");
    auto resp = client1->Post(rsp.href, xml::Serialize(rsp));
    std::cout << resp << std::endl;
    //EXPECT_EQ(resp.result_int(), 201);
}

TEST_F(HttpsResponseTests, GetResponse)
{
    HttpsClient *client1 = HttpsClient::getInstance("1", g_program_path, "0.0.0.0", "8080");
    try
    {
        auto resp = client1->Get("/rsp");
        std::string msg = boost::beast::buffers_to_string(resp.body().data());
        EXPECT_TRUE(validator->ValidateXml(msg));

        sep::DeviceCapability dcap;
        xml::Parse(msg, &dcap);
        EXPECT_TRUE(dcap.href == "/rsp");       
    }
    catch (const std::exception &e)
    {
        ASSERT_ANY_THROW(e.what());
    }
}

TEST_F(HttpsResponseTests, PutResponse)
{
    EXPECT_TRUE(false);
}

TEST_F(HttpsResponseTests, DeleteResponse)
{
    EXPECT_TRUE(false);
}