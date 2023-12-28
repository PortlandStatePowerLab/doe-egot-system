

#include <gtest/gtest.h>
#include <sep/xml/der_settings_adapter.hpp>.hpp>
#include <sep/xml/utilities.hpp>
#include <sep/xml/xml_validator.hpp>
#include <string>
#include <utilities/utilities.hpp>

extern std::string g_program_path;

class TestDERSettingsXML : public ::testing::Test {
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

TEST_F(TestDERSettingsXML, IsSampleValid) {
  EXPECT_TRUE(validator->ValidateXml(xml_str));
}

TEST_F(TestDERSettingsXML, IsAdapterValid) { EXPECT_TRUE(false); }

TEST_F(TestDERSettingsXML, IsAdapterTranslationAccurate) { EXPECT_TRUE(false); }
