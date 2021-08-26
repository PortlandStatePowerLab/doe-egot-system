#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <climits>
#include <algorithm>
#include <gtest/gtest.h>
#include <sep/models.hpp>
#include <xml/adapter.hpp>
#include <xml/xml_validator.hpp>
#include "global.hpp"

class TestSelfDeviceXML : public ::testing::Test 
{
protected:
    void SetUp() override 
    {        
        validator = new XmlValidator(g_program_path + "/sep.xsd");

        // read in the sample file
        std::ifstream ifs(g_program_path + "/SelfDevice.xml");
        if (ifs)
        {
            std::ostringstream oss;
            oss << ifs.rdbuf();
            xml_str = oss.str();        
        }
        else
        {
            std::cout << "couldn't open xml file" << std::endl;
        };
    }

    void TearDown() override
    {
        delete validator;
    }

protected:
    std::string xml_str;
    XmlValidator *validator;
};

TEST_F(TestSelfDeviceXML, IsSampleValid) 
{   
    EXPECT_TRUE(validator->ValidateXml(xml_str));      
}

TEST_F(TestSelfDeviceXML, IsAdapterValid) 
{   
    sep::SelfDevice *sdev = new sep::SelfDevice;
    xml::Parse(xml_str, sdev);
    EXPECT_TRUE(validator->ValidateXml(xml::Serialize(*sdev)));
    delete sdev;
}

TEST_F(TestSelfDeviceXML, IsAdapterTranslationAccurate) 
{   
    sep::SelfDevice *sdev = new sep::SelfDevice;
    xml::Parse(xml_str, sdev);
    EXPECT_EQ(sdev->poll_rate, 900);
    EXPECT_EQ(xml::util::ToUnderlyingType(sdev->subscribable), 0);
    EXPECT_EQ(sdev->href, "http://uri1");
    EXPECT_EQ(sdev->configuration_link, "http://uri1");
    EXPECT_EQ(sdev->der_list_link, "http://uri1");
    EXPECT_EQ(xml::util::ToUnderlyingType(sdev->device_category), 0x0FB7);
    EXPECT_EQ(sdev->device_information_link, "http://uri1");
    EXPECT_EQ(sdev->device_status_link, "http://uri1");
    EXPECT_EQ(sdev->file_status_link, "http://uri1");
    EXPECT_EQ(sdev->ip_interface_list_link, "http://uri1");
    EXPECT_EQ(sdev->lfdi, "0FB7");
    EXPECT_EQ(sdev->load_shed_availability_list_link, "http://uri1");
    EXPECT_EQ(sdev->log_event_list_link, "http://uri1");
    EXPECT_EQ(sdev->power_status_link, "http://uri1");
    EXPECT_EQ(sdev->sfdi, 0);
    delete sdev;
}
