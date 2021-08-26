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

class TestActivePowerXML : public ::testing::Test 
{
protected:
    void SetUp() override 
    {        
        validator = new XmlValidator(g_program_path + "/sep.xsd");

        // read in the sample file
        std::ifstream ifs(g_program_path + "/ActivePower.xml");
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

TEST_F(TestActivePowerXML, IsSampleValid) 
{   
    EXPECT_TRUE(validator->ValidateXml(xml_str));      
}

TEST_F(TestActivePowerXML, IsAdapterValid) 
{   
    // create model, convert it into a string and then reparse to see if the string was valid
    sep::ActivePower *active_power = new sep::ActivePower;
    xml::Parse(xml_str, active_power);
    EXPECT_TRUE(validator->ValidateXml(xml::Serialize(*active_power)));
    delete active_power;
}

TEST_F(TestActivePowerXML, IsAdapterTranslationAccurate) 
{   
    // create model, convert it into a string and then reparse to see if the string was valid
    sep::ActivePower *active_power = new sep::ActivePower;
    xml::Parse(xml_str, active_power);
    EXPECT_EQ(active_power->multiplier, 1);
    EXPECT_EQ(active_power->value, -32000);
    delete active_power;
}

TEST_F(TestActivePowerXML, CheckAdapterMultiplierMaxInclusive) 
{   
    boost::property_tree::ptree pt;
    pt.put("ActivePower.multiplier", 10);
    pt.put("ActivePower.value", -32000);
    std::string xml_adapter = xml::util::Stringify(pt);
    EXPECT_FALSE(validator->ValidateXml(xml_adapter));
}

TEST_F(TestActivePowerXML, CheckAdapterMultiplierMinInclusive) 
{   
    boost::property_tree::ptree pt;
    pt.put("ActivePower.multiplier", -10);
    pt.put("ActivePower.value", -32000);
    std::string xml_adapter = xml::util::Stringify(pt);
    EXPECT_FALSE(validator->ValidateXml(xml_adapter));
}

TEST_F(TestActivePowerXML, CheckAdapterValueMaxInclusive) 
{   
    boost::property_tree::ptree pt;
    pt.put("ActivePower.multiplier", 1);
    pt.put("ActivePower.value", 32768);
    std::string xml_adapter = xml::util::Stringify(pt);
    EXPECT_FALSE(validator->ValidateXml(xml_adapter));
}

TEST_F(TestActivePowerXML, CheckAdapterValueMinInclusive) 
{   
    boost::property_tree::ptree pt;
    pt.put("ActivePower.multiplier", 1);
    pt.put("ActivePower.value", -32769);
    std::string xml_adapter = xml::util::Stringify(pt);
    EXPECT_FALSE(validator->ValidateXml(xml_adapter));
}