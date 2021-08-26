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

class TestEndDeviceXML : public ::testing::Test 
{
protected:
    void SetUp() override 
    {        
        validator = new XmlValidator(g_program_path + "/sep.xsd");

        // read in the sample file
        std::ifstream ifs(g_program_path + "/EndDevice.xml");
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

TEST_F(TestEndDeviceXML, IsSampleValid) 
{   
    EXPECT_TRUE(validator->ValidateXml(xml_str));      
}

TEST_F(TestEndDeviceXML, IsAdapterValid) 
{   
    sep::EndDevice *edev = new sep::EndDevice;
    xml::Parse(xml_str, edev);
    EXPECT_TRUE(validator->ValidateXml(xml::Serialize(*edev)));
    delete edev;
}

TEST_F(TestEndDeviceXML, IsAdapterTranslationAccurate) 
{   
    sep::EndDevice *edev = new sep::EndDevice;
    xml::Parse(xml_str, edev);
    EXPECT_EQ(xml::util::ToUnderlyingType(edev->subscribable), 0);
    EXPECT_EQ(edev->href, "http://uri1");
    EXPECT_EQ(edev->configuration_link, "http://uri1");
    EXPECT_EQ(edev->der_list_link, "http://uri1");
    EXPECT_EQ(xml::util::ToUnderlyingType(edev->device_category), 0x0FB7);
    EXPECT_EQ(edev->device_information_link, "http://uri1");
    EXPECT_EQ(edev->device_status_link, "http://uri1");
    EXPECT_EQ(edev->file_status_link, "http://uri1");
    EXPECT_EQ(edev->ip_interface_list_link, "http://uri1");
    EXPECT_EQ(edev->lfdi, "0FB7");
    EXPECT_EQ(edev->load_shed_availability_list_link, "http://uri1");
    EXPECT_EQ(edev->log_event_list_link, "http://uri1");
    EXPECT_EQ(edev->power_status_link, "http://uri1");
    EXPECT_EQ(edev->sfdi, 0);
    EXPECT_EQ(edev->changed_time, 1);
    EXPECT_EQ(edev->enabled, true);
    EXPECT_EQ(edev->flow_reservation_request_list_link, "http://uri1");
    EXPECT_EQ(edev->flow_reservation_response_list_link, "http://uri1");
    EXPECT_EQ(edev->function_set_assignments_list_link, "http://uri1");
    EXPECT_EQ(edev->post_rate, 0);
    EXPECT_EQ(edev->registration_link, "http://uri1");
    EXPECT_EQ(edev->subscription_list_link, "http://uri1");
    delete edev;
}

TEST_F(TestEndDeviceXML, CheckAdapterDeviceCategoryMaxValue) 
{   
    boost::property_tree::ptree pt;
    pt.put("EndDevice.<xmlattr>.subscribable", 0);
    pt.put("EndDevice.<xmlattr>.href", "http://uri1");
    pt.put("EndDevice.ConfigurationLink.<xmlattr>.href", "http://uri1");
    pt.put("EndDevice.DERListLink.<xmlattr>.href", "http://uri1");
    pt.put("EndDevice.deviceCategory", "4000000");
    pt.put("EndDevice.DeviceInformationLink.<xmlattr>.href", "http://uri1");
    pt.put("EndDevice.DeviceStatusLink.<xmlattr>.href", "http://uri1");
    pt.put("EndDevice.FileStatusLink.<xmlattr>.href", "http://uri1");
    pt.put("EndDevice.IPInterfaceListLink.<xmlattr>.href", "http://uri1");
    pt.put("EndDevice.lFDI", "0FB7");
    pt.put("EndDevice.LoadShedAvailabilityListLink.<xmlattr>.href", "http://uri1");
    pt.put("EndDevice.LogEventListLink.<xmlattr>.href", "http://uri1");
    pt.put("EndDevice.PowerStatusLink.<xmlattr>.href", "http://uri1");
    pt.put("EndDevice.sFDI", 0);
    pt.put("EndDevice.changedTime", 1);
    pt.put("EndDevice.enabled", true);
    pt.put("EndDevice.FlowReservationRequestListLink.<xmlattr>.href", "http://uri1");
    pt.put("EndDevice.FlowReservationResponseListLink.<xmlattr>.href", "http://uri1");
    pt.put("EndDevice.FunctionSetAssignmentsListLink.<xmlattr>.href", "http://uri1");
    pt.put("EndDevice.postRate", 0);
    pt.put("EndDevice.RegistrationLink.<xmlattr>.href", "http://uri1");
    pt.put("EndDevice.SubscriptionListLink.<xmlattr>.href", "http://uri1");

    std::string xml_adapter = xml::util::Stringify(pt);
    EXPECT_FALSE(validator->ValidateXml(xml_adapter));
}