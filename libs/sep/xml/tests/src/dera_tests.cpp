
#include "sep/models/der_availability.hpp"
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

    xml_str = psu::utilities::readFile(g_program_path +
                                       "/sep_xml/DERAvailability.xml");
  }

  void TearDown() override { delete validator; }

protected:
  std::string xml_str;
  XmlValidator *validator;
};

TEST_F(TestDERAvailabilityXML, IsSampleValid) {
  EXPECT_TRUE(validator->ValidateXml(xml_str));
}

TEST_F(TestDERAvailabilityXML, IsAdapterValid) {
  sep::DERAvailability dera;
  xml::Parse(xml_str, &dera);

  EXPECT_TRUE(validator->ValidateXml(xml::Serialize(dera)));
}

TEST_F(TestDERAvailabilityXML, IsAdapterTranslationAccurate) {
  sep::DERAvailability dera;
  xml::Parse(xml_str, &dera);

  std::string uri = "http://uri1";
  EXPECT_EQ(dera.href, uri);
  EXPECT_EQ(dera.reading_time, 1);

  if (dera.availability_duration.is_initialized()) {
    EXPECT_EQ(dera.availability_duration.value(), 0);
  }
  if (dera.max_charge_duration.is_initialized()) {
    EXPECT_EQ(dera.max_charge_duration.value(), 0);
  }
  if (dera.reserve_charge_percent.is_initialized()) {
    EXPECT_EQ(dera.reserve_charge_percent.value(), 0);
  }
  if (dera.reserve_percent.is_initialized()) {
    EXPECT_EQ(dera.reserve_percent.value(), 0);
  }
  if (dera.stat_var_avail.is_initialized()) {
    EXPECT_EQ(dera.stat_var_avail->multiplier, 1);
    EXPECT_EQ(dera.stat_var_avail->value, 1);
  }
  if (dera.stat_w_avail.is_initialized()) {
    EXPECT_EQ(dera.stat_w_avail->multiplier, 1);
    EXPECT_EQ(dera.stat_w_avail->value, 1);
  }
}
