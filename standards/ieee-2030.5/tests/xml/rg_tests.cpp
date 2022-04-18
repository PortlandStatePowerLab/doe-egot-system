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

class TestRegistrationML : public ::testing::Test 
{
protected:
    void SetUp() override 
    {        
        validator = new XmlValidator(g_program_path + "/sep_xml/sep.xsd");

        xml_str = psu::utilities::readFile(g_program_path + "/sep_xml/Registration.xml");
    }

    void TearDown() override
    {
        delete validator;
    }

protected:
    std::string xml_str;
    XmlValidator *validator;
};

TEST_F(TestRegistrationML, IsSampleValid) 
{   
    EXPECT_TRUE(validator->ValidateXml(xml_str));      
}

TEST_F(TestRegistrationML, IsAdapterValid) 
{   
    sep::Registration* rg = new sep::Registration;
    xml::Parse(xml_str, rg);
    EXPECT_TRUE(validator->ValidateXml(xml::Serialize(*rg)));
    delete rg;
}


TEST_F(TestRegistrationML, IsAdapterTranslationAccurate) 
{   
    sep::Registration* rg = new sep::Registration;
    xml::Parse(xml_str, rg);
    EXPECT_EQ(rg->href, "http://uri1");
    EXPECT_EQ(rg->poll_rate, 900);
    EXPECT_EQ(rg->date_time_registered, 1);
    EXPECT_EQ(rg->pin, 0);
    delete rg;
}