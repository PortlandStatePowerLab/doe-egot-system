#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <climits>
#include <algorithm>
#include <gtest/gtest.h>
#include <ieee-2030.5/models.hpp>
#include <xml/adapter.hpp>
#include <xml/xml_validator.hpp>
#include <utilities/utilities.hpp>

extern std::string g_program_path;

class TestDeviceCapabilityXML : public ::testing::Test 
{
protected:
    void SetUp() override 
    {        
        validator = new XmlValidator(g_program_path + "/sep_xml/sep.xsd");

        xml_str = psu::utilities::readFile(g_program_path+"/sep_xml/DeviceCapability.xml");;
    }

    void TearDown() override
    {
        delete validator;
    }

protected:
    std::string xml_str;
    XmlValidator *validator;
};

TEST_F(TestDeviceCapabilityXML, IsSampleValid) 
{   
    EXPECT_TRUE(validator->ValidateXml(xml_str));      
}

TEST_F(TestDeviceCapabilityXML, IsAdapterValid) 
{   
    sep::DeviceCapability *dcap = new sep::DeviceCapability;
    xml::Parse(xml_str, dcap);
    EXPECT_TRUE(validator->ValidateXml(xml::Serialize(*dcap)));
    delete dcap;
}

TEST_F(TestDeviceCapabilityXML, IsAdapterTranslationAccurate) 
{   
    sep::DeviceCapability *dcap = new sep::DeviceCapability;
    xml::Parse(xml_str, dcap);
    EXPECT_EQ(dcap->poll_rate, 900);
    EXPECT_EQ(dcap->href, "http://uri1");
    EXPECT_EQ(dcap->customer_account_list_link.href, "http://uri1");
    EXPECT_EQ(dcap->customer_account_list_link.all, 0);
    EXPECT_EQ(dcap->demand_response_program_list_link.href, "http://uri1");
    EXPECT_EQ(dcap->demand_response_program_list_link.all, 0);
    EXPECT_EQ(dcap->der_program_list_link.href, "http://uri1");
    EXPECT_EQ(dcap->der_program_list_link.all, 0);
    EXPECT_EQ(dcap->file_list_link.href, "http://uri1");
    EXPECT_EQ(dcap->file_list_link.all, 0);
    EXPECT_EQ(dcap->messaging_program_list_link.href, "http://uri1");
    EXPECT_EQ(dcap->messaging_program_list_link.all, 0);
    EXPECT_EQ(dcap->prepayment_list_link.href, "http://uri1");
    EXPECT_EQ(dcap->prepayment_list_link.all, 0);
    EXPECT_EQ(dcap->response_set_list_link.href, "http://uri1");
    EXPECT_EQ(dcap->response_set_list_link.all, 0);
    EXPECT_EQ(dcap->tariff_profile_list_link.href, "http://uri1");
    EXPECT_EQ(dcap->tariff_profile_list_link.all, 0);
    EXPECT_EQ(dcap->time_link.href, "http://uri1");
    EXPECT_EQ(dcap->usage_point_list_link.href, "http://uri1");
    EXPECT_EQ(dcap->usage_point_list_link.all, 0);
    EXPECT_EQ(dcap->end_device_list_link.href, "http://uri1");
    EXPECT_EQ(dcap->end_device_list_link.all, 0);
    EXPECT_EQ(dcap->mirror_usage_point_list_link.href, "http://uri1");
    EXPECT_EQ(dcap->mirror_usage_point_list_link.all, 0);
    EXPECT_EQ(dcap->self_device_link.href, "http://uri1");
    delete dcap;
}