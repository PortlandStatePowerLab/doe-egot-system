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
        list_xml_str = psu::utilities::readFile(g_program_path + "/sep_xml/ResponseSetList.xml");
    }

    void TearDown() override
    {
        delete validator;
    }

protected:
    std::string xml_str;
    std::string list_xml_str;
    XmlValidator *validator;
};

TEST_F(TestResponseSetXML, IsSampleValid) 
{   
    EXPECT_TRUE(validator->ValidateXml(xml_str));      
}

TEST_F(TestResponseSetXML, IsAdapterValid) 
{   
    sep::ResponseSet rsps;
    xml::Parse(xml_str, &rsps);
    EXPECT_TRUE(validator->ValidateXml(xml::Serialize(rsps)));
}


TEST_F(TestResponseSetXML, IsAdapterTranslationAccurate) 
{   
    sep::ResponseSet rsps;
    xml::Parse(xml_str, &rsps);

    EXPECT_EQ(rsps.href, "http://uri1");
    EXPECT_EQ(rsps.mrid, 0x0FB7);
    EXPECT_EQ(rsps.description, "description1");
    EXPECT_EQ(rsps.version, 0);
    EXPECT_EQ(rsps.response_list_link.all, 0);
    EXPECT_EQ(rsps.response_list_link.href, "http://uri1");
}

TEST_F(TestResponseSetXML, IsListSampleValid) 
{   
    EXPECT_TRUE(validator->ValidateXml(list_xml_str));      
}

TEST_F(TestResponseSetXML, IsListAdapterValid) 
{   
    std::vector<sep::ResponseSet> rsps_list;
    xml::Parse(list_xml_str, &rsps_list);
    EXPECT_TRUE(validator->ValidateXml(xml::Serialize(rsps_list)));
}