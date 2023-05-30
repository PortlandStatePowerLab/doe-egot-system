#include <algorithm>
#include <climits>
#include <fstream>
#include <gtest/gtest.h>
#include <iostream>
#include <memory>
#include <sep/xml/power_status_adapter.hpp>
#include <sep/xml/utilities.hpp>
#include <sep/xml/xml_validator.hpp>
#include <string>
#include <utilities/utilities.hpp>

extern std::string g_program_path;

class TestPowerStatusXML : public ::testing::Test {
protected:
  void SetUp() override {
    validator = new XmlValidator(g_program_path + "/sep_xml/sep.xsd");

    xml_str =
        psu::utilities::readFile(g_program_path + "/sep_xml/PowerStatus.xml");
  }

  void TearDown() override { delete validator; }

protected:
  std::string xml_str;
  XmlValidator *validator;
};

TEST_F(TestPowerStatusXML, IsSampleValid) {
  EXPECT_TRUE(validator->ValidateXml(xml_str));
}

TEST_F(TestPowerStatusXML, IsAdapterValid) {
  sep::PowerStatus ps;
  xml::Parse(xml_str, &ps);
  EXPECT_TRUE(validator->ValidateXml(xml::Serialize(ps)));
}

TEST_F(TestPowerStatusXML, IsAdapterTranslationAccurate) {
  sep::PowerStatus ps;
  xml::Parse(xml_str, &ps);
  EXPECT_EQ(ps.poll_rate, 900);
  EXPECT_EQ(ps.href, "http://uri1");
  EXPECT_EQ(xml::util::ToUnderlyingType(ps.battery_status), 0);
  EXPECT_EQ(ps.changed_time, 1);
  EXPECT_EQ(xml::util::ToUnderlyingType(ps.current_power_source), 0);
  EXPECT_EQ(ps.estimated_charge_remaining.value(), 0);
  EXPECT_EQ(ps.estimated_time_remaining.value(), 0);
  EXPECT_EQ(ps.pev_info.value().charging_power_now.multiplier, 1);
  EXPECT_EQ(ps.pev_info.value().charging_power_now.value, 1);
  EXPECT_EQ(ps.pev_info.value().energy_request_now.multiplier, 1);
  EXPECT_EQ(ps.pev_info.value().energy_request_now.value, 0);
  EXPECT_EQ(ps.pev_info.value().max_forward_power.multiplier, 1);
  EXPECT_EQ(ps.pev_info.value().max_forward_power.value, 1);
  EXPECT_EQ(ps.pev_info.value().minimum_charging_duration, 0);
  EXPECT_EQ(ps.pev_info.value().target_state_of_charge, 0);
  EXPECT_EQ(ps.pev_info.value().time_charge_is_needed, 1);
  EXPECT_EQ(ps.pev_info.value().time_charging_status_pev, 1);
  EXPECT_EQ(ps.session_time_on_battery.value(), 0);
  EXPECT_EQ(ps.total_time_on_battery.value(), 0);
}

TEST_F(TestPowerStatusXML, IsOptional) {
  sep::PowerStatus ps;
  ps.href = "/ps";
  ps.poll_rate = 900;
  ps.battery_status = sep::BatteryStatus::kUnknown;
  ps.changed_time = 123;
  ps.current_power_source = sep::PowerSourceType::kMains;
  EXPECT_TRUE(validator->ValidateXml(xml::Serialize(ps)));
}