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

class TestResponseSetXML : public ::testing::Test 
{
protected:
    void SetUp() override 
    {        
        validator = new XmlValidator(g_program_path + "/sep_xml/sep.xsd");

        xml_str = psu::utilities::readFile(g_program_path + "/sep_xml/ResponseSet.xml");
    }

    void TearDown() override
    {
        delete validator;
    }

protected:
    std::string xml_str;
    XmlValidator *validator;
};

TEST_F(TestResponseSetXML, IsSampleValid) 
{   
    EXPECT_TRUE(validator->ValidateXml(xml_str));      
}

TEST_F(TestResponseSetXML, IsAdapterValid) 
{   
    EXPECT_TRUE(false);
}


TEST_F(TestResponseSetXML, IsAdapterTranslationAccurate) 
{   
    EXPECT_TRUE(false);
}