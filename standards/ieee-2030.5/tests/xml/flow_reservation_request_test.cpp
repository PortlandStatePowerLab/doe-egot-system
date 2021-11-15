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

class TestFlowReservationRequestXML : public ::testing::Test 
{
protected:
    void SetUp() override 
    {        
        validator = new XmlValidator(g_program_path + "/sep.xsd");

        // read in the sample file
        std::ifstream ifs(g_program_path + "/FlowReservationRequest.xml");
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

TEST_F(TestFlowReservationRequestXML, IsSampleValid) 
{   
    EXPECT_TRUE(validator->ValidateXml(xml_str));      
}

TEST_F(TestFlowReservationRequestXML, IsAdapterValid) 
{   
    sep::FlowReservationRequest *fr_request = new sep::FlowReservationRequest;
    xml::Parse(xml_str, fr_request);
    EXPECT_TRUE(validator->ValidateXml(xml::Serialize(*fr_request)));
    delete fr_request;
}


TEST_F(TestFlowReservationRequestXML, IsAdapterTranslationAccurate) 
{   
    sep::FlowReservationRequest *fr_request = new sep::FlowReservationRequest;
    xml::Parse(xml_str, fr_request);
    EXPECT_EQ(fr_request->mrid,"0FB7");
    EXPECT_EQ(fr_request->description, "description1");
    EXPECT_EQ(fr_request->version, 0);
    EXPECT_EQ(fr_request->creation_time, 1);
    EXPECT_EQ(fr_request->duration_requested, 0);
    EXPECT_EQ(fr_request->energy_requested.multiplier, 1);
    EXPECT_EQ(fr_request->energy_requested.value, -140737488355328);
    EXPECT_EQ(fr_request->interval_requested.duration, 0);
    EXPECT_EQ(fr_request->interval_requested.start, 1);
    EXPECT_EQ(fr_request->power_requested.multiplier,1);
    EXPECT_EQ(fr_request->power_requested.value, 1);
    EXPECT_EQ(fr_request->request_status.datetime,1);
    EXPECT_EQ(xml::util::ToUnderlyingType(fr_request->request_status.status), 0);
    delete fr_request;
}

TEST_F(TestFlowReservationRequestXML, CheckAdapterStatusMaxInclusive) 
{   
    boost::property_tree::ptree pt;
    pt.put("FlowReservationRequest.mRID", "0FB7");
    pt.put("FlowReservationRequest.description", "description1");
    pt.put("FlowReservationRequest.version", 0);
    pt.put("FlowReservationRequest.creationTime", 1);
    pt.put("FlowReservationRequest.durationRequested", 0);
    pt.put("FlowReservationRequest.energyRequested.multiplier", 1);
    pt.put("FlowReservationRequest.energyRequested.value", -140737488355328);
    pt.put("FlowReservationRequest.intervalRequested.duration", 0);
    pt.put("FlowReservationRequest.intervalRequested.start", 1);
    pt.put("FlowReservationRequest.powerRequested.multiplier", 1);
    pt.put("FlowReservationRequest.powerRequested.value", 1);
    pt.put("FlowReservationRequest.RequestStatus.dateTime", 1);
    pt.put("FlowReservationRequest.RequestStatus.requestStatus", 2);

    std::string xml_adapter = xml::util::Stringify(pt);
    EXPECT_FALSE(validator->ValidateXml(xml_adapter));
}

TEST_F(TestFlowReservationRequestXML, CheckAdapterStatusMinInclusive) 
{   
    boost::property_tree::ptree pt;
    pt.put("FlowReservationRequest.mRID", "0FB7");
    pt.put("FlowReservationRequest.description", "description1");
    pt.put("FlowReservationRequest.version", 0);
    pt.put("FlowReservationRequest.creationTime", 1);
    pt.put("FlowReservationRequest.durationRequested", 0);
    pt.put("FlowReservationRequest.energyRequested.multiplier", 1);
    pt.put("FlowReservationRequest.energyRequested.value", -140737488355328);
    pt.put("FlowReservationRequest.intervalRequested.duration", 0);
    pt.put("FlowReservationRequest.intervalRequested.start", 1);
    pt.put("FlowReservationRequest.powerRequested.multiplier", 1);
    pt.put("FlowReservationRequest.powerRequested.value", 1);
    pt.put("FlowReservationRequest.RequestStatus.dateTime", 1);
    pt.put("FlowReservationRequest.RequestStatus.requestStatus", -1);

    std::string xml_adapter = xml::util::Stringify(pt);
    EXPECT_FALSE(validator->ValidateXml(xml_adapter));
}