

#include <gtest/gtest.h>
#include <sep/xml/der_settings_adapter.hpp>
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
        psu::utilities::readFile(g_program_path + "/sep_xml/DERSettings.xml");
  }

  void TearDown() override { delete validator; }

protected:
  std::string xml_str;
  XmlValidator *validator;
};

TEST_F(TestDERSettingsXML, IsSampleValid) {
  EXPECT_TRUE(validator->ValidateXml(xml_str));
}

TEST_F(TestDERSettingsXML, IsAdapterValid) {
  sep::DERSettings derg;
  xml::Parse(xml_str, &derg);
  EXPECT_TRUE(validator->ValidateXml(xml::Serialize(derg)));
}

TEST_F(TestDERSettingsXML, IsAdapterTranslationAccurate) {
  sep::DERSettings derg;
  xml::Parse(xml_str, &derg);

  std::cout << xml::Serialize(derg) << std::endl;

  std::string uri = "http://uri1";
  EXPECT_EQ(derg.href, uri);
  EXPECT_EQ(derg.set_max_w.value, 1);
  EXPECT_EQ(derg.set_max_w.multiplier, 7);
  EXPECT_EQ(derg.set_grad_w, 0);
  EXPECT_EQ(derg.updated_time, 1);

  if (derg.set_es_random_delay.is_initialized()) {
    EXPECT_EQ(derg.set_es_random_delay.value(), 0);
  }

  if (derg.set_es_high_freq.is_initialized()) {
    EXPECT_EQ(derg.set_es_high_freq.value(), 0);
  }

  if (derg.set_es_high_volt.is_initialized()) {
    EXPECT_EQ(derg.set_es_high_volt.value(), 1);
  }

  if (derg.set_es_low_freq.is_initialized()) {
    EXPECT_EQ(derg.set_es_low_freq.value(), 0);
  }

  if (derg.set_es_low_volt.is_initialized()) {
    EXPECT_EQ(derg.set_es_low_volt.value(), 1);
  }

  if (derg.set_es_ramp_tms.is_initialized()) {
    EXPECT_EQ(derg.set_es_ramp_tms.value(), 0);
  }

  if (derg.set_es_random_delay.is_initialized()) {
    EXPECT_EQ(derg.set_es_random_delay.value(), 0);
  }

  if (derg.set_max_a.is_initialized()) {
    EXPECT_EQ(derg.set_max_a->value, 0);
    EXPECT_EQ(derg.set_max_a->multiplier, 1);
  }

  if (derg.set_max_ah.is_initialized()) {
    EXPECT_EQ(derg.set_max_ah->value, 0);
    EXPECT_EQ(derg.set_max_ah->multiplier, 1);
  }

  if (derg.set_max_charge_rate_va.is_initialized()) {
    EXPECT_EQ(derg.set_max_charge_rate_va->value, 0);
    EXPECT_EQ(derg.set_max_charge_rate_va->multiplier, 1);
  }

  if (derg.set_max_charge_rate_w.is_initialized()) {
    EXPECT_EQ(derg.set_max_charge_rate_w->value, 1);
    EXPECT_EQ(derg.set_max_charge_rate_w->multiplier, 1);
  }

  if (derg.set_max_discharge_rate_va.is_initialized()) {
    EXPECT_EQ(derg.set_max_discharge_rate_va->value, 0);
    EXPECT_EQ(derg.set_max_discharge_rate_va->multiplier, -8);
  }

  if (derg.set_max_v.is_initialized()) {
    EXPECT_EQ(derg.set_max_v->value, 0);
    EXPECT_EQ(derg.set_max_v->multiplier, -8);
  }

  if (derg.set_max_va.is_initialized()) {
    EXPECT_EQ(derg.set_max_va->value, 0);
    EXPECT_EQ(derg.set_max_va->multiplier, 7);
  }

  if (derg.set_max_var.is_initialized()) {
    EXPECT_EQ(derg.set_max_var->value, 1);
    EXPECT_EQ(derg.set_max_var->multiplier, 1);
  }

  if (derg.set_max_var_neg.is_initialized()) {
    EXPECT_EQ(derg.set_max_var_neg->value, 1);
    EXPECT_EQ(derg.set_max_var_neg->multiplier, -8);
  }

  if (derg.set_max_wh.is_initialized()) {
    EXPECT_EQ(derg.set_max_wh->value, 0);
    EXPECT_EQ(derg.set_max_wh->multiplier, 1);
  }

  if (derg.set_min_pf_over_excited.is_initialized()) {
    EXPECT_EQ(derg.set_min_pf_over_excited->displacement, 0);
    EXPECT_EQ(derg.set_min_pf_over_excited->multiplier, 1);
  }

  if (derg.set_min_pf_under_excited.is_initialized()) {
    EXPECT_EQ(derg.set_min_pf_under_excited->displacement, 0);
    EXPECT_EQ(derg.set_min_pf_under_excited->multiplier, -8);
  }

  if (derg.set_min_v.is_initialized()) {
    EXPECT_EQ(derg.set_max_v->value, 0);
    EXPECT_EQ(derg.set_max_v->multiplier, -8);
  }

  if (derg.set_soft_grad_w.is_initialized()) {
    EXPECT_EQ(derg.set_soft_grad_w.value(), 0);
  }

  if (derg.set_v_nom.is_initialized()) {
    EXPECT_EQ(derg.set_v_nom->value, 0);
    EXPECT_EQ(derg.set_v_nom->multiplier, 7);
  }

  if (derg.set_v_ref.is_initialized()) {
    EXPECT_EQ(derg.set_v_ref->value, 0);
    EXPECT_EQ(derg.set_v_ref->multiplier, 0);
  }

  if (derg.set_v_ref_ofs.is_initialized()) {
    EXPECT_EQ(derg.set_v_ref_ofs->value, 0);
    EXPECT_EQ(derg.set_v_ref_ofs->multiplier, 2);
  }
}
