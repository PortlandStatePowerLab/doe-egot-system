#include <string>
#include <thread>
#include <fstream>
#include <gtest/gtest.h>
#include <https/https_server.hpp>
#include <https/https_client.hpp>
#include <xml/adapter.hpp>
#include <xml/xml_validator.hpp>
#include <wadl/wadl.hpp>
#include <ieee-2030.5/end_device.hpp>

extern std::string g_program_path;

class HttpsEndDeviceTests : public ::testing::Test
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

TEST_F(HttpsEndDeviceTests, GetEndDevice)
{
    HttpsClient *client1 = HttpsClient::getInstance("1", g_program_path, "0.0.0.0", "8080");
    try
    {
        auto resp = client1->Get("/edev");

        std::cout << "DEBUG: HTTS response \n";
        for (const auto& field : resp)
        {
            std::cout << field.name() << " = " << field.value() << "\n";
        }

        std::string msg = boost::beast::buffers_to_string(resp.body().data());
        EXPECT_TRUE(validator->ValidateXml(msg));

        std::vector<sep::EndDevice> edev_list;
        xml::Parse(msg, &edev_list);
        EXPECT_EQ(edev_list.size(),1);
        EXPECT_TRUE(edev_list[0].href == "/edev");
        EXPECT_EQ(edev_list[0].lfdi,client1->getLFDI());
    }
    catch (const std::exception &e)
    {
        ASSERT_ANY_THROW(e.what());
    }
}

TEST_F(HttpsEndDeviceTests, PostEndDevice)
{
    HttpsClient *client1 = HttpsClient::getInstance("1", g_program_path, "0.0.0.0", "8080");
    try
    {
        auto resp = client1->Get("/edev");    
        std::string msg = boost::beast::buffers_to_string(resp.body().data());

        std::vector<sep::EndDevice> edev_list;
        xml::Parse(msg, &edev_list);
        
        resp = client1->Post("/edev", xml::Serialize(edev_list[0]));

        std::cout << "DEBUG: HTTS response \n";
        for (const auto& field : resp)
        {
            std::cout << field.name() << " = " << field.value() << "\n";
        }

        EXPECT_EQ(resp.base().result_int(), 200);        
    }
    catch (const std::exception &e)
    {
        ASSERT_ANY_THROW(e.what());
    }
}

TEST_F(HttpsEndDeviceTests, PutEndDevice)
{
    HttpsClient *client1 = HttpsClient::getInstance("1", g_program_path, "0.0.0.0", "8080");
    try
    {
        auto resp = client1->Get("/edev");    
        std::string msg = boost::beast::buffers_to_string(resp.body().data());

        std::vector<sep::EndDevice> edev_list;
        xml::Parse(msg, &edev_list);
        
        resp = client1->Put("/edev", xml::Serialize(edev_list[0]));

        std::cout << "DEBUG: HTTS response \n";
        for (const auto& field : resp)
        {
            std::cout << field.name() << " = " << field.value() << "\n";
        }

        EXPECT_EQ(resp.base().result_int(), 405);
    }
    catch (const std::exception &e)
    {
        ASSERT_ANY_THROW(e.what());
    }
}

TEST_F(HttpsEndDeviceTests, DeleteEndDevice)
{
    HttpsClient *client1 = HttpsClient::getInstance("1", g_program_path, "0.0.0.0", "8080");
    try
    {
        auto resp = client1->Get("/edev");    
        std::string msg = boost::beast::buffers_to_string(resp.body().data());

        std::vector<sep::EndDevice> edev_list;
        xml::Parse(msg, &edev_list);
        
        resp = client1->Delete("/edev");

        std::cout << "DEBUG: HTTS response \n";
        for (const auto& field : resp)
        {
            std::cout << field.name() << " = " << field.value() << "\n";
        }

        EXPECT_EQ(resp.base().result_int(), 405);
    }
    catch (const std::exception &e)
    {
        ASSERT_ANY_THROW(e.what());
    }
}