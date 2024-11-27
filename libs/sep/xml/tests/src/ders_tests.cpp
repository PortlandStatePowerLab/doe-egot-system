

#include <gtest/gtest.h>
#include <sep/xml/der_status_adapter.hpp>
#include <sep/xml/utilities.hpp>
#include <sep/xml/xml_validator.hpp>
#include <string>
#include <utilities/utilities.hpp>

extern std::string g_program_path;

class TestDERStatusXML : public ::testing::Test {
protected:
  void SetUp() override {
    validator = new XmlValidator(g_program_path + "/sep_xml/sep.xsd");

    xml_str =
        psu::utilities::readFile(g_program_path + "/sep_xml/DERStatus.xml");
  }

  void TearDown() override { delete validator; }

protected:
  std::string xml_str;
  XmlValidator *validator;
};

TEST_F(TestDERStatusXML, IsSampleValid) {
  EXPECT_TRUE(validator->ValidateXml(xml_str));
}

TEST_F(TestDERStatusXML, IsAdapterValid) {
  sep::DERStatus ders;
  xml::Parse(xml_str, &ders);
  EXPECT_TRUE(validator->ValidateXml(xml::Serialize(ders)));
}

TEST_F(TestDERStatusXML, IsAdapterTranslationAccurate) {
  sep::DERStatus ders;
  xml::Parse(xml_str, &ders);

  std::string uri = "http://uri1";
  EXPECT_EQ(ders.href, uri);
  if (ders.alarm_status.is_initialized()) {
    EXPECT_EQ(ders.alarm_status.value(),
              sep::DERStatus::AlarmStatus::kOverVoltage);
  }

  if (ders.gen_connection_status.is_initialized()) {
    EXPECT_EQ(ders.gen_connection_status->date_time, 1);
    EXPECT_EQ(
        xml::util::ToUnderlyingType(ders.gen_connection_status->value),
        xml::util::ToUnderlyingType(sep::ConnectStatusType::Status::kTest));
  }

  if (ders.inverter_status.is_initialized()) {
    EXPECT_EQ(ders.inverter_status->date_time, 1);
    EXPECT_EQ(ders.inverter_status->value,
              sep::InverterStatusType::Status::kNA);
  }

  if (ders.local_control_mode_status.is_initialized()) {
    EXPECT_EQ(ders.local_control_mode_status->date_time, 1);
    EXPECT_EQ(ders.local_control_mode_status->value,
              sep::LocalControlModeStatusType::ControlStatus::kLocal);
  }

  if (ders.manufacturer_status.is_initialized()) {
    EXPECT_EQ(ders.manufacturer_status->date_time, 1);
    EXPECT_EQ(ders.manufacturer_status->value, "value1");
  }

  if (ders.operational_mode_status.is_initialized()) {
    EXPECT_EQ(ders.operational_mode_status->date_time, 1);
    EXPECT_EQ(ders.operational_mode_status->value,
              sep::OperationalModeStatusType::Status::kNA);
  }

  if (ders.state_of_charge_status.is_initialized()) {
    EXPECT_EQ(ders.state_of_charge_status->date_time, 1);
    EXPECT_EQ(ders.state_of_charge_status->value, 0);
  }

  if (ders.storage_mode_status.is_initialized()) {
    EXPECT_EQ(ders.storage_mode_status->date_time, 1);
    EXPECT_EQ(ders.storage_mode_status->value,
              sep::StorageModeStatusType::Status::kCharging);
  }

  if (ders.stor_connect_status.is_initialized()) {
    EXPECT_EQ(ders.stor_connect_status->date_time, -9223372036854775807);
    EXPECT_EQ(
        xml::util::ToUnderlyingType(ders.stor_connect_status->value),
        xml::util::ToUnderlyingType(sep::ConnectStatusType::Status::kTest));
  }
}
