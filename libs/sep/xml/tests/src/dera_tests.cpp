
#include <gtest/gtest.h>
#include <sep/xml/der_availability_adapter.hpp>
#include <sep/xml/utilities.hpp>
#include <sep/xml/xml_validator.hpp>
#include <string>
#include <utilities/utilities.hpp>

extern std::string g_program_path;

class TestDERAvailabilityXML : public ::testing::Test {
protected:
  void SetUp() override {
    validator = new XmlValidator(g_program_path + "/sep_xml/sep.xsd");

    xml_str =
        psu::utilities::readFile(g_program_path + "/sep_xml/Notification.xml");
  }

  void TearDown() override { delete validator; }

protected:
  std::string xml_str;
  XmlValidator *validator;
};

TEST_F(TestDERAvailabilityXML, IsSampleValid) {
  EXPECT_TRUE(validator->ValidateXml(xml_str));
}

TEST_F(TestDERAvailabilityXML, IsAdapterValid) { EXPECT_TRUE(false); }

TEST_F(TestDERAvailabilityXML, IsAdapterTranslationAccurate) {
  EXPECT_TRUE(false);
}
