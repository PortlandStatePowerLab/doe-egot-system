#ifndef __DER_SETTINGS_H__
#define __DER_SETTINGS_H__
#include "active_power.hpp"
#include "ampere_hour.hpp"
#include "apparent_power.hpp"
#include "current_rms.hpp"
#include "der_control_type.hpp"
#include "power_factor.hpp"
#include "reactive_power.hpp"
#include "simple_types.hpp"
#include "subscribable_resource.hpp"
#include "voltage_rms.hpp"
#include "watt_hour.hpp"
#include <boost/optional.hpp>

namespace sep {
struct DERSettingsLink : Link {};

///
/// Distributed energy resource settings
///
struct DERSettings : SubscribableResource {

  UInt16 set_grad_w;
  ActivePower set_max_w;
  TimeType updated_time;
  boost::optional<DERControlType> modes_enabled;
  boost::optional<UInt32> set_es_delay;
  boost::optional<UInt16> set_es_high_freq;
  boost::optional<UInt16> set_es_low_freq;
  boost::optional<UInt16> set_es_high_volt;
  boost::optional<UInt16> set_es_low_volt;
  boost::optional<UInt32> set_es_ramp_tms;
  boost::optional<UInt32> set_es_random_delay;
  boost::optional<UInt16> set_soft_grad_w;
  boost::optional<CurrentRMS> set_max_a;
  boost::optional<AmpereHour> set_max_ah;
  boost::optional<ApparentPower> set_max_charge_rate_va;
  boost::optional<ActivePower> set_max_charge_rate_w;
  boost::optional<ApparentPower> set_max_discharge_rate_va;
  boost::optional<ActivePower> set_max_discharge_rate_w;
  boost::optional<VoltageRMS> set_max_v;
  boost::optional<ApparentPower> set_max_va;
  boost::optional<ReactivePower> set_max_var;
  boost::optional<ReactivePower> set_max_var_neg;
  boost::optional<WattHour> set_max_wh;
  boost::optional<PowerFactor> set_min_pf_over_excited;
  boost::optional<PowerFactor> set_min_pf_under_excited;
  boost::optional<VoltageRMS> set_min_v;
  boost::optional<VoltageRMS> set_v_nom;
  boost::optional<VoltageRMS> set_v_ref;
  boost::optional<VoltageRMS> set_v_ref_ofs;
};

} // namespace sep

#endif // __DER_SETTINGS_H__
