#ifndef __DER_CONTROL_BASE_H__
#define __DER_CONTROL_BASE_H__
#include "active_power.hpp"
#include "der_curve.hpp"
#include "fixed_var.hpp"
#include "freq_droop_type.hpp"
#include "per_cent.hpp"
#include "power_factor_with_excitation.hpp"
#include "reactive_power.hpp"
#include "signed_per_cent.hpp"
#include "simple_types.hpp"

namespace sep {
///
/// Distributed Energy Resource (DER) control values.
///
struct DERControlBase {
  bool op_mod_connect;
  bool op_mod_energize;
  PowerFactorWithExcitation op_mod_fixed_pf_absorb_w;
  PowerFactorWithExcitation op_mod_fixed_pf_inject_w;
  FixedVAR op_mod_fixed_var;
  SignedPerCent op_mod_fixed_w;
  FreqDroopType op_mod_freq_droop;
  DERCurveLink op_mod_freq_watt;
  DERCurveLink op_mod_hfrt_may_trip;
  DERCurveLink op_mod_hfrt_must_trip;
  DERCurveLink op_mod_hvrt_may_trip;
  DERCurveLink op_mod_hvrt_momentary_cessation;
  DERCurveLink op_mod_hvrt_must_trip;
  DERCurveLink op_mod_lfrt_may_trip;
  DERCurveLink op_mod_lvrt_momentary_cessation;
  DERCurveLink op_mod_lvrt_must_trip;
  PerCent op_mod_max_lim_w;
  ReactivePower op_mod_target_var;
  ActivePower op_mod_target_w;
  Link op_mod_volt_var;
  Link op_mod_volt_watt;
  Link op_mod_watt_pf;
  Link op_mod_watt_var;
  uint16_t ramp_tms; // ramp time, in hundredths of a second
};
};     // namespace sep
#endif // __DER_CONTROL_BASE_H__
