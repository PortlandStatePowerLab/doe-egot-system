

#include "sep/models/subscribable_type.hpp"
#include <gtest/gtest.h>
#include <sep/xml/der_adapter.hpp>
#include <sep/xml/utilities.hpp>
#include <sep/xml/xml_validator.hpp>
#include <string>
#include <utilities/utilities.hpp>

extern std::string g_program_path;

class TestDERXML : public ::testing::Test {
protected:
  void SetUp() override {
    validator = new XmlValidator(g_program_path + "/sep_xml/sep.xsd");

    xml_str = psu::utilities::readFile(g_program_path + "/sep_xml/DER.xml");
  }

  void TearDown() override { delete validator; }

protected:
  std::string xml_str;
  XmlValidator *validator;
};

TEST_F(TestDERXML, IsSampleValid) {
  EXPECT_TRUE(validator->ValidateXml(xml_str));
}

TEST_F(TestDERXML, IsAdapterValid) {
  sep::DER der;
  xml::Parse(xml_str, &der);
  EXPECT_TRUE(validator->ValidateXml(xml::Serialize(der)));
}

TEST_F(TestDERXML, IsAdapterTranslationAccurate) {
  sep::DER der;
  xml::Parse(xml_str, &der);

  std::string uri = "http://uri1";
  EXPECT_TRUE(der.href == uri);
  EXPECT_TRUE(der.subscribable == sep::SubscribableType::kNone);
  EXPECT_TRUE(der.associated_der_program_list_link->href == uri);
  EXPECT_TRUE(der.associated_der_program_list_link->all == 0);
  EXPECT_TRUE(der.associated_usage_program_link->href == uri);
  EXPECT_TRUE(der.current_der_program_link->href == uri);
  EXPECT_TRUE(der.der_availability_link->href == uri);
  EXPECT_TRUE(der.der_capability_link->href == uri);
  EXPECT_TRUE(der.der_settings_link->href == uri);
  EXPECT_TRUE(der.der_status_link->href == uri);
}
