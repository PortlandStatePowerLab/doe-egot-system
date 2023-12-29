#include "sep/models/der_capability.hpp"
#include <gtest/gtest.h>
#include <sep/xml/der_capability_adapter.hpp>
#include <sep/xml/utilities.hpp>
#include <sep/xml/xml_validator.hpp>
#include <string>
#include <utilities/utilities.hpp>

extern std::string g_program_path;

class TestDERCapabilityXML : public ::testing::Test {
protected:
  void SetUp() override {
    validator = new XmlValidator(g_program_path + "/sep_xml/sep.xsd");

    xml_str =
        psu::utilities::readFile(g_program_path + "/sep_xml/DERCapability.xml");
  }

  void TearDown() override { delete validator; }

protected:
  std::string xml_str;
  XmlValidator *validator;
};

TEST_F(TestDERCapabilityXML, IsSampleValid) {
  EXPECT_TRUE(validator->ValidateXml(xml_str));
}

TEST_F(TestDERCapabilityXML, IsAdapterValid) {
  sep::DERCapability dercap;
  xml::Parse(xml_str, &dercap);
  EXPECT_TRUE(validator->ValidateXml(xml::Serialize(dercap)));
}

TEST_F(TestDERCapabilityXML, IsAdapterTranslationAccurate) {
  sep::DERCapability dercap;
  xml::Parse(xml_str, &dercap);

  std::cout << xml::Serialize(dercap) << std::endl;

  std::string uri = "http://uri1";
  EXPECT_EQ(dercap.href, uri);
  EXPECT_EQ(dercap.type, sep::DERType::kNA);
  EXPECT_EQ(dercap.rtg_max_w.value, 1);
  EXPECT_EQ(dercap.rtg_max_w.multiplier, 7);
  if (dercap.rtg_max_a.is_initialized()) {
    EXPECT_EQ(dercap.rtg_max_a.get().value, 0);
    EXPECT_EQ(dercap.rtg_max_a.get().multiplier, 1);
  }

  if (dercap.rtg_max_ah.is_initialized()) {
    EXPECT_EQ(dercap.rtg_max_ah.get().value, 0);
    EXPECT_EQ(dercap.rtg_max_ah.get().multiplier, 1);
  }

  if (dercap.rtg_max_charge_rate_va.is_initialized()) {
    EXPECT_EQ(dercap.rtg_max_charge_rate_va.get().value, 0);
    EXPECT_EQ(dercap.rtg_max_charge_rate_va.get().multiplier, 1);
  }

  if (dercap.rtg_max_charge_rate_w.is_initialized()) {
    EXPECT_EQ(dercap.rtg_max_charge_rate_w.get().value, 1);
    EXPECT_EQ(dercap.rtg_max_charge_rate_w.get().multiplier, 1);
  }

  if (dercap.rtg_max_discharge_rate_va.is_initialized()) {
    EXPECT_EQ(dercap.rtg_max_discharge_rate_va.get().value, 0);
    EXPECT_EQ(dercap.rtg_max_discharge_rate_va.get().multiplier, -8);
  }

  if (dercap.rtg_max_v.is_initialized()) {
    EXPECT_EQ(dercap.rtg_max_v.get().value, 0);
    EXPECT_EQ(dercap.rtg_max_v.get().multiplier, -8);
  }

  if (dercap.rtg_max_va.is_initialized()) {
    EXPECT_EQ(dercap.rtg_max_va.get().value, 0);
    EXPECT_EQ(dercap.rtg_max_va.get().multiplier, 7);
  }

  if (dercap.rtg_max_var.is_initialized()) {
    EXPECT_EQ(dercap.rtg_max_var.get().value, 1);
    EXPECT_EQ(dercap.rtg_max_var.get().multiplier, 1);
  }

  if (dercap.rtg_max_var_neg.is_initialized()) {
    EXPECT_EQ(dercap.rtg_max_var_neg.get().value, 1);
    EXPECT_EQ(dercap.rtg_max_var_neg.get().multiplier, -8);
  }

  if (dercap.rtg_max_wh.is_initialized()) {
    EXPECT_EQ(dercap.rtg_max_wh.get().value, 0);
    EXPECT_EQ(dercap.rtg_max_wh.get().multiplier, 1);
  }

  if (dercap.rtg_min_pf_over_excited.is_initialized()) {
    EXPECT_EQ(dercap.rtg_min_pf_over_excited.get().displacement, 0);
    EXPECT_EQ(dercap.rtg_min_pf_over_excited.get().multiplier, 1);
  }

  if (dercap.rtg_min_pf_under_excited.is_initialized()) {
    EXPECT_EQ(dercap.rtg_min_pf_under_excited.get().displacement, 0);
    EXPECT_EQ(dercap.rtg_min_pf_under_excited.get().multiplier, -8);
  }

  if (dercap.rtg_min_v.is_initialized()) {
    EXPECT_EQ(dercap.rtg_max_v.get().value, 0);
    EXPECT_EQ(dercap.rtg_max_v.get().multiplier, -8);
  }

  if (dercap.rtg_normal_category.is_initialized()) {
    EXPECT_EQ(dercap.rtg_normal_category.get(),
              sep::DERCapability::NormalCategory::kNotSpecified);
  }

  if (dercap.rtg_over_excited_pf.is_initialized()) {
    EXPECT_EQ(dercap.rtg_over_excited_pf.get().displacement, 0);
    EXPECT_EQ(dercap.rtg_over_excited_pf.get().multiplier, 7);
  }

  if (dercap.rtg_over_excited_w.is_initialized()) {
    EXPECT_EQ(dercap.rtg_over_excited_w.get().value, 1);
    EXPECT_EQ(dercap.rtg_over_excited_w.get().multiplier, 0);
  }

  if (dercap.rtg_reactive_susceptance.is_initialized()) {
    EXPECT_EQ(dercap.rtg_reactive_susceptance.get().value, 0);
    EXPECT_EQ(dercap.rtg_reactive_susceptance.get().multiplier, 1);
  }

  if (dercap.rtg_under_excited_pf.is_initialized()) {
    EXPECT_EQ(dercap.rtg_under_excited_pf.get().displacement, 0);
    EXPECT_EQ(dercap.rtg_under_excited_pf.get().multiplier, 0);
  }

  if (dercap.rtg_under_excited_w.is_initialized()) {
    EXPECT_EQ(dercap.rtg_under_excited_w.get().value, 1);
    EXPECT_EQ(dercap.rtg_under_excited_w.get().multiplier, 2);
  }

  if (dercap.rtg_v_nom.is_initialized()) {
    EXPECT_EQ(dercap.rtg_v_nom.get().value, 0);
    EXPECT_EQ(dercap.rtg_v_nom.get().multiplier, 7);
  }
}
