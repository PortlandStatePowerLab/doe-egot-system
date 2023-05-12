#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <climits>
#include <algorithm>
#include <gtest/gtest.h>
// #include <sep/xml/notification_adapter.hpp>
#include <sep/xml/xml_validator.hpp>
#include <sep/xml/utilities.hpp>
#include <utilities/utilities.hpp>

extern std::string g_program_path;

class TestNotificationXML : public ::testing::Test 
{
protected:
    void SetUp() override 
    {        
        validator = new XmlValidator(g_program_path + "/sep_xml/sep.xsd");

        xml_str = psu::utilities::readFile(g_program_path + "/sep_xml/Notification.xml");
    }

    void TearDown() override
    {
        delete validator;
    }

protected:
    std::string xml_str;
    XmlValidator *validator;
};

TEST_F(TestNotificationXML, IsSampleValid) 
{   
    EXPECT_TRUE(validator->ValidateXml(xml_str));      
}

TEST_F(TestNotificationXML, IsAdapterValid) 
{   
    EXPECT_TRUE(false);
}


TEST_F(TestNotificationXML, IsAdapterTranslationAccurate) 
{   
    EXPECT_TRUE(false);
}