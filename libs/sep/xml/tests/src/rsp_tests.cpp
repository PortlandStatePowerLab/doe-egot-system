#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <climits>
#include <algorithm>
#include <gtest/gtest.h>
#include <sep/xml/response_adapter.hpp>
#include <sep/xml/xml_validator.hpp>
#include <sep/xml/utilities.hpp>
#include <utilities/utilities.hpp>

extern std::string g_program_path;

class TestResponseXML : public ::testing::Test 
{
protected:
    void SetUp() override 
    {        
        validator = new XmlValidator(g_program_path + "/sep_xml/sep.xsd");

        xml_str = psu::utilities::readFile(g_program_path + "/sep_xml/Response.xml");
        list_xml_str = psu::utilities::readFile(g_program_path + "/sep_xml/ResponseList.xml");
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

TEST_F(TestResponseXML, IsSampleValid) 
{   
    EXPECT_TRUE(validator->ValidateXml(xml_str));      
}

TEST_F(TestResponseXML, IsAdapterValid) 
{   
    sep::Response rsp;
    xml::Parse(xml_str, &rsp);
    EXPECT_TRUE(validator->ValidateXml(xml::Serialize(rsp)));
}


TEST_F(TestResponseXML, IsAdapterTranslationAccurate) 
{   
    sep::Response rsp;
    xml::Parse(xml_str, &rsp);
    
    EXPECT_EQ(rsp.href, "http://uri1");
    EXPECT_EQ(rsp.end_device_lfdi, 0x0FB7);
    EXPECT_EQ(rsp.created_date_time.value(), 1);
    EXPECT_EQ(
        xml::util::ToUnderlyingType<sep::Response::Status>(rsp.status.value()), 
        0
    );
    EXPECT_EQ(rsp.subject, 0x0FB7);
}

TEST_F(TestResponseXML, IsListSampleValid) 
{   
    EXPECT_TRUE(validator->ValidateXml(list_xml_str));      
}

TEST_F(TestResponseXML, IsListAdapterValid) 
{   
    sep::ResponseList rsp_list;
    xml::Parse(list_xml_str, &rsp_list);
    EXPECT_TRUE(validator->ValidateXml(xml::Serialize(rsp_list)));
}