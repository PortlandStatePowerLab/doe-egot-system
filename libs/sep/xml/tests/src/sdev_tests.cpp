#include <algorithm>
#include <climits>
#include <fstream>
#include <gtest/gtest.h>
#include <iostream>
#include <memory>
#include <sep/xml/self_device_adapter.hpp>
#include <sep/xml/utilities.hpp>
#include <sep/xml/xml_validator.hpp>
#include <string>
#include <utilities/utilities.hpp>

extern std::string g_program_path;

class TestSelfDeviceXML : public ::testing::Test {
protected:
  void SetUp() override {
    validator = new XmlValidator(g_program_path + "/sep_xml/sep.xsd");

    xml_str =
        psu::utilities::readFile(g_program_path + "/sep_xml/SelfDevice.xml");
  }

  void TearDown() override { delete validator; }

protected:
  std::string xml_str;
  XmlValidator *validator;
};

TEST_F(TestSelfDeviceXML, IsSampleValid) {
  EXPECT_TRUE(validator->ValidateXml(xml_str));
}

TEST_F(TestSelfDeviceXML, IsAdapterValid) {
  sep::SelfDevice sdev;
  xml::Parse(xml_str, &sdev);
  EXPECT_TRUE(validator->ValidateXml(xml::Serialize(sdev)));
}

TEST_F(TestSelfDeviceXML, IsAdapterTranslationAccurate) {
  sep::SelfDevice sdev;
  xml::Parse(xml_str, &sdev);
  EXPECT_EQ(sdev.poll_rate, 900);
  EXPECT_EQ(xml::util::ToUnderlyingType(sdev.subscribable), 0);
  EXPECT_EQ(sdev.href, "http://uri1");
  EXPECT_EQ(sdev.configuration_link.value().href, "http://uri1");
  EXPECT_EQ(sdev.der_list_link.value().href, "http://uri1");
  EXPECT_EQ(sdev.der_list_link.value().all, 0);
  EXPECT_EQ(xml::util::ToUnderlyingType(sdev.device_category.value()), 0x0FB7);
  EXPECT_EQ(sdev.device_information_link.value().href, "http://uri1");
  EXPECT_EQ(sdev.device_status_link.value().href, "http://uri1");
  EXPECT_EQ(sdev.file_status_link.value().href, "http://uri1");
  EXPECT_EQ(sdev.ip_interface_list_link.value().href, "http://uri1");
  EXPECT_EQ(sdev.ip_interface_list_link.value().all, 0);
  EXPECT_EQ(sdev.lfdi.value(), 0x0FB7);
  EXPECT_EQ(sdev.load_shed_availability_list_link.value().href, "http://uri1");
  EXPECT_EQ(sdev.load_shed_availability_list_link.value().all, 0);
  EXPECT_EQ(sdev.log_event_list_link.value().href, "http://uri1");
  EXPECT_EQ(sdev.log_event_list_link.value().all, 0);
  EXPECT_EQ(sdev.power_status_link.value().href, "http://uri1");
  EXPECT_EQ(sdev.sfdi, 0);
}

TEST_F(TestSelfDeviceXML, IsOptional) {
  sep::SelfDevice sdev;
  sdev.href = "/sdev";
  sdev.poll_rate = 900;
  EXPECT_TRUE(validator->ValidateXml(xml::Serialize(sdev)));
}