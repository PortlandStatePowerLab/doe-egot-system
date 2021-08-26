#ifndef __DER_CONTROL_BASE_H__
#define __DER_CONTROL_BASE_H__
#include <string>
#include <cstdint>
#include "power_factor_with_excitation.hpp"
#include "fixed_var.hpp"
#include "signed_per_cent.hpp"
#include "freq_droop_type.hpp"
#include "per_cent.hpp"
#include "reactive_power.hpp"
#include "active_power.hpp"
#include "der_curve_link.hpp"

namespace sep
{
    // Distributed Energy Resource (DER) control values.
    struct DERControlBase
    {
        bool op_mod_connect;
        bool op_mod_energize;
        sep::PowerFactorWithExcitation op_mod_fixed_pf_absorb_w;
        sep::PowerFactorWithExcitation op_mod_fixed_pf_inject_w;
        sep::FixedVAR op_mod_fixed_var;
        sep::SignedPerCent op_mod_fixed_w;
        sep::FreqDroopType op_mod_freq_droop;
        sep::DERCurveLink op_mod_freq_watt;
        sep::DERCurveLink op_mod_hfrt_may_trip;
        sep::DERCurveLink op_mod_hfrt_must_trip;
        sep::DERCurveLink op_mod_hvrt_may_trip;
        sep::DERCurveLink op_mod_hvrt_momentary_cessation;
        sep::DERCurveLink op_mod_hvrt_must_trip;
        sep::DERCurveLink op_mod_lfrt_may_trip;
        sep::DERCurveLink op_mod_lvrt_momentary_cessation;
        sep::DERCurveLink op_mod_lvrt_must_trip;
        sep::PerCent op_mod_max_lim_w;
        sep::ReactivePower op_mod_target_var;
        sep::ActivePower op_mod_target_w;
        sep::DERCurveLink op_mod_volt_var;
        sep::DERCurveLink op_mod_volt_watt;
        sep::DERCurveLink op_mod_watt_pf;
        sep::DERCurveLink op_mod_watt_var;
        uint16_t ramp_tms; // ramp time, in hundredths of a second
    };
};     // namespace sep
#endif // __DER_CONTROL_BASE_H__