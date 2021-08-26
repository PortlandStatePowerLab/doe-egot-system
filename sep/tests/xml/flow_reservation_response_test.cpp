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

class TestFlowReservationResponseXML : public ::testing::Test 
{
protected:
    void SetUp() override 
    {        
        validator = new XmlValidator(g_program_path + "/sep.xsd");

        // read in the sample file
        std::ifstream ifs(g_program_path + "/FlowReservationResponse.xml");
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

TEST_F(TestFlowReservationResponseXML, IsSampleValid) 
{   
    EXPECT_TRUE(validator->ValidateXml(xml_str));      
}

TEST_F(TestFlowReservationResponseXML, IsAdapterValid) 
{   
    sep::FlowReservationResponse *fr_response = new sep::FlowReservationResponse;
    xml::Parse(xml_str, fr_response);
    EXPECT_TRUE(validator->ValidateXml(xml::Serialize(*fr_response)));
    delete fr_response;
}

TEST_F(TestFlowReservationResponseXML, IsAdapterTranslationAccurate) 
{   
    sep::FlowReservationResponse *fr_response = new sep::FlowReservationResponse;
    xml::Parse(xml_str, fr_response);
    EXPECT_EQ(xml::util::ToUnderlyingType(fr_response->subscribable), 0);
    EXPECT_EQ(fr_response->reply_to, "http://uri1");
    EXPECT_EQ(xml::util::Hexify(xml::util::ToUnderlyingType(fr_response->response_required)), "00");
    EXPECT_EQ(fr_response->href, "http://uri1");
    EXPECT_EQ(fr_response->mrid,"0FB7");
    EXPECT_EQ(fr_response->description, "description1");
    EXPECT_EQ(fr_response->version, 0);
    EXPECT_EQ(fr_response->creation_time, 1);
    EXPECT_EQ(xml::util::ToUnderlyingType(fr_response->event_status.current_status), 0);
    EXPECT_EQ(fr_response->event_status.date_time, 1);
    EXPECT_EQ(fr_response->event_status.potentially_superseded, true);
    EXPECT_EQ(fr_response->event_status.potentially_superseded_time, 1);
    EXPECT_EQ(fr_response->event_status.reason, "reason1");
    EXPECT_EQ(fr_response->interval.duration,0);
    EXPECT_EQ(fr_response->interval.start, 1);
    EXPECT_EQ(fr_response->energy_available.multiplier,1);
    EXPECT_EQ(fr_response->energy_available.value,-140737488355328);
    EXPECT_EQ(fr_response->power_available.multiplier,1);
    EXPECT_EQ(fr_response->power_available.value,1);
    EXPECT_EQ(fr_response->subject, "0FB7");
    delete fr_response;
}

TEST_F(TestFlowReservationResponseXML, CheckAdapterSubscribableMaxInclusive) 
{   
    boost::property_tree::ptree pt;
    pt.put("FlowReservationResponse.<xmlattr>.subscribable", 4);
    pt.put("FlowReservationResponse.<xmlattr>.replyTo", "http://uri1");
    pt.put("FlowReservationResponse.<xmlattr>.responseRequired", "00");
    pt.put("FlowReservationResponse.<xmlattr>.href", "http://uri1");
    pt.put("FlowReservationResponse.mRID", "0FB7");
    pt.put("FlowReservationResponse.description", "description1");
    pt.put("FlowReservationResponse.version", 0);
    pt.put("FlowReservationResponse.creationTime", 1);
    pt.put("FlowReservationResponse.EventStatus.currentStatus", 0);
    pt.put("FlowReservationResponse.EventStatus.dateTime", 1);
    pt.put("FlowReservationResponse.EventStatus.potentiallySuperseded", true);
    pt.put("FlowReservationResponse.EventStatus.potentiallySupersededTime", 1);
    pt.put("FlowReservationResponse.EventStatus.reason", "reason1");
    pt.put("FlowReservationResponse.interval.duration", 0);
    pt.put("FlowReservationResponse.interval.start", 1);
    pt.put("FlowReservationResponse.energyAvailable.multiplier", 1);
    pt.put("FlowReservationResponse.energyAvailable.value", -140737488355328);
    pt.put("FlowReservationResponse.powerAvailable.multiplier", 1);
    pt.put("FlowReservationResponse.powerAvailable.value", 1);
    pt.put("FlowReservationResponse.subject", "0FB7");

    std::string xml_adapter = xml::util::Stringify(pt);
    EXPECT_FALSE(validator->ValidateXml(xml_adapter));
}

TEST_F(TestFlowReservationResponseXML, CheckAdapterSubscribableMinInclusive) 
{   
    boost::property_tree::ptree pt;
    pt.put("FlowReservationResponse.<xmlattr>.subscribable", -1);
    pt.put("FlowReservationResponse.<xmlattr>.replyTo", "http://uri1");
    pt.put("FlowReservationResponse.<xmlattr>.responseRequired", "00");
    pt.put("FlowReservationResponse.<xmlattr>.href", "http://uri1");
    pt.put("FlowReservationResponse.mRID", "0FB7");
    pt.put("FlowReservationResponse.description", "description1");
    pt.put("FlowReservationResponse.version", 0);
    pt.put("FlowReservationResponse.creationTime", 1);
    pt.put("FlowReservationResponse.EventStatus.currentStatus", 0);
    pt.put("FlowReservationResponse.EventStatus.dateTime", 1);
    pt.put("FlowReservationResponse.EventStatus.potentiallySuperseded", true);
    pt.put("FlowReservationResponse.EventStatus.potentiallySupersededTime", 1);
    pt.put("FlowReservationResponse.EventStatus.reason", "reason1");
    pt.put("FlowReservationResponse.interval.duration", 0);
    pt.put("FlowReservationResponse.interval.start", 1);
    pt.put("FlowReservationResponse.energyAvailable.multiplier", 1);
    pt.put("FlowReservationResponse.energyAvailable.value", -140737488355328);
    pt.put("FlowReservationResponse.powerAvailable.multiplier", 1);
    pt.put("FlowReservationResponse.powerAvailable.value", 1);
    pt.put("FlowReservationResponse.subject", "0FB7");

    std::string xml_adapter = xml::util::Stringify(pt);
    EXPECT_FALSE(validator->ValidateXml(xml_adapter));
}

TEST_F(TestFlowReservationResponseXML, CheckAdapterResponseRequiredMaxInclusive) 
{   
    boost::property_tree::ptree pt;
    pt.put("FlowReservationResponse.<xmlattr>.subscribable", 0);
    pt.put("FlowReservationResponse.<xmlattr>.replyTo", "http://uri1");
    pt.put("FlowReservationResponse.<xmlattr>.responseRequired", "04");
    pt.put("FlowReservationResponse.<xmlattr>.href", "http://uri1");
    pt.put("FlowReservationResponse.mRID", "0FB7");
    pt.put("FlowReservationResponse.description", "description1");
    pt.put("FlowReservationResponse.version", 0);
    pt.put("FlowReservationResponse.creationTime", 1);
    pt.put("FlowReservationResponse.EventStatus.currentStatus", 0);
    pt.put("FlowReservationResponse.EventStatus.dateTime", 1);
    pt.put("FlowReservationResponse.EventStatus.potentiallySuperseded", true);
    pt.put("FlowReservationResponse.EventStatus.potentiallySupersededTime", 1);
    pt.put("FlowReservationResponse.EventStatus.reason", "reason1");
    pt.put("FlowReservationResponse.interval.duration", 0);
    pt.put("FlowReservationResponse.interval.start", 1);
    pt.put("FlowReservationResponse.energyAvailable.multiplier", 1);
    pt.put("FlowReservationResponse.energyAvailable.value", -140737488355328);
    pt.put("FlowReservationResponse.powerAvailable.multiplier", 1);
    pt.put("FlowReservationResponse.powerAvailable.value", 1);
    pt.put("FlowReservationResponse.subject", "0FB7");

    std::string xml_adapter = xml::util::Stringify(pt);
    EXPECT_FALSE(validator->ValidateXml(xml_adapter));
}

TEST_F(TestFlowReservationResponseXML, CheckAdapterResponseRequiredNonHex) 
{   
    boost::property_tree::ptree pt;
    pt.put("FlowReservationResponse.<xmlattr>.subscribable", 0);
    pt.put("FlowReservationResponse.<xmlattr>.replyTo", "http://uri1");
    pt.put("FlowReservationResponse.<xmlattr>.responseRequired", "0");
    pt.put("FlowReservationResponse.<xmlattr>.href", "http://uri1");
    pt.put("FlowReservationResponse.mRID", "0FB7");
    pt.put("FlowReservationResponse.description", "description1");
    pt.put("FlowReservationResponse.version", 0);
    pt.put("FlowReservationResponse.creationTime", 1);
    pt.put("FlowReservationResponse.EventStatus.currentStatus", 0);
    pt.put("FlowReservationResponse.EventStatus.dateTime", 1);
    pt.put("FlowReservationResponse.EventStatus.potentiallySuperseded", true);
    pt.put("FlowReservationResponse.EventStatus.potentiallySupersededTime", 1);
    pt.put("FlowReservationResponse.EventStatus.reason", "reason1");
    pt.put("FlowReservationResponse.interval.duration", 0);
    pt.put("FlowReservationResponse.interval.start", 1);
    pt.put("FlowReservationResponse.energyAvailable.multiplier", 1);
    pt.put("FlowReservationResponse.energyAvailable.value", -140737488355328);
    pt.put("FlowReservationResponse.powerAvailable.multiplier", 1);
    pt.put("FlowReservationResponse.powerAvailable.value", 1);
    pt.put("FlowReservationResponse.subject", "0FB7");

    std::string xml_adapter = xml::util::Stringify(pt);
    EXPECT_FALSE(validator->ValidateXml(xml_adapter));
}

TEST_F(TestFlowReservationResponseXML, CheckAdapterResponseCurrentStatusMaxInclusive) 
{   
    boost::property_tree::ptree pt;
    pt.put("FlowReservationResponse.<xmlattr>.subscribable", 0);
    pt.put("FlowReservationResponse.<xmlattr>.replyTo", "http://uri1");
    pt.put("FlowReservationResponse.<xmlattr>.responseRequired", "00");
    pt.put("FlowReservationResponse.<xmlattr>.href", "http://uri1");
    pt.put("FlowReservationResponse.mRID", "0FB7");
    pt.put("FlowReservationResponse.description", "description1");
    pt.put("FlowReservationResponse.version", 0);
    pt.put("FlowReservationResponse.creationTime", 1);
    pt.put("FlowReservationResponse.EventStatus.currentStatus", 5);
    pt.put("FlowReservationResponse.EventStatus.dateTime", 1);
    pt.put("FlowReservationResponse.EventStatus.potentiallySuperseded", true);
    pt.put("FlowReservationResponse.EventStatus.potentiallySupersededTime", 1);
    pt.put("FlowReservationResponse.EventStatus.reason", "reason1");
    pt.put("FlowReservationResponse.interval.duration", 0);
    pt.put("FlowReservationResponse.interval.start", 1);
    pt.put("FlowReservationResponse.energyAvailable.multiplier", 1);
    pt.put("FlowReservationResponse.energyAvailable.value", -140737488355328);
    pt.put("FlowReservationResponse.powerAvailable.multiplier", 1);
    pt.put("FlowReservationResponse.powerAvailable.value", 1);
    pt.put("FlowReservationResponse.subject", "0FB7");

    std::string xml_adapter = xml::util::Stringify(pt);
    EXPECT_FALSE(validator->ValidateXml(xml_adapter));
}

TEST_F(TestFlowReservationResponseXML, CheckAdapterResponseCurrentStatusMinInclusive) 
{   
    boost::property_tree::ptree pt;
    pt.put("FlowReservationResponse.<xmlattr>.subscribable", 0);
    pt.put("FlowReservationResponse.<xmlattr>.replyTo", "http://uri1");
    pt.put("FlowReservationResponse.<xmlattr>.responseRequired", "00");
    pt.put("FlowReservationResponse.<xmlattr>.href", "http://uri1");
    pt.put("FlowReservationResponse.mRID", "0FB7");
    pt.put("FlowReservationResponse.description", "description1");
    pt.put("FlowReservationResponse.version", 0);
    pt.put("FlowReservationResponse.creationTime", 1);
    pt.put("FlowReservationResponse.EventStatus.currentStatus", -1);
    pt.put("FlowReservationResponse.EventStatus.dateTime", 1);
    pt.put("FlowReservationResponse.EventStatus.potentiallySuperseded", true);
    pt.put("FlowReservationResponse.EventStatus.potentiallySupersededTime", 1);
    pt.put("FlowReservationResponse.EventStatus.reason", "reason1");
    pt.put("FlowReservationResponse.interval.duration", 0);
    pt.put("FlowReservationResponse.interval.start", 1);
    pt.put("FlowReservationResponse.energyAvailable.multiplier", 1);
    pt.put("FlowReservationResponse.energyAvailable.value", -140737488355328);
    pt.put("FlowReservationResponse.powerAvailable.multiplier", 1);
    pt.put("FlowReservationResponse.powerAvailable.value", 1);
    pt.put("FlowReservationResponse.subject", "0FB7");

    std::string xml_adapter = xml::util::Stringify(pt);
    EXPECT_FALSE(validator->ValidateXml(xml_adapter));
}