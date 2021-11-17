#ifndef __DER_SETTINGS_H__
#define __DER_SETTINGS_H__
#include <cstdint>
#include "subscribable_resource.hpp"
#include "der_control_type.hpp"
#include "power_factor_with_excitation.hpp"
#include "der_control_type.hpp"
#include "current_rms.hpp"
#include "ampere_hour.hpp"
#include "apparent_power.hpp"
#include "active_power.hpp"
#include "voltage_rms.hpp"
#include "reactive_power.hpp"
#include "watt_hour.hpp"
#include "power_factor.hpp"
#include "der_type.hpp"
#include "time_type.hpp"

namespace sep
{
    // Distributed energy resource settings
    struct DERSettings : SubscribableResource
    {
        DERControlType modes_enabled;
        uint32_t set_es_delay;
        uint16_t set_es_high_freq;
        uint16_t set_es_high_volt;
        uint16_t set_es_low_freq;
        uint16_t set_es_low_volt;
        uint32_t set_es_ramp_tms;
        uint32_t set_es_random_delay;
        uint16_t set_grad_w;
        uint16_t set_soft_grad_w; 
        CurrentRMS set_max_a;
        AmpereHour set_max_ah;
        ApparentPower set_max_charge_rate_va;
        ActivePower set_max_charge_rate_w;
        ApparentPower set_max_discharge_rate_va;
        ActivePower set_max_discharge_rate_w;
        VoltageRMS set_max_v;
        ApparentPower set_max_va;
        ReactivePower set_max_var;
        ReactivePower set_max_var_neg;
        ActivePower set_max_w;
        WattHour set_max_wh;
        PowerFactor set_min_pf_over_excited;
        VoltageRMS set_min_v;
        PowerFactor set_over_excited_pf;
        ActivePower set_over_excited_w;
        ReactivePower set_reactive_susceptance;
        PowerFactor set_under_excited_pf;
        ActivePower set_under_excited_w;
        VoltageRMS set_v_nom;
        VoltageRMS set_v_ref;
        VoltageRMS set_vref_fofs;
        TimeType update_time;
        DERType type;
    };
    
} // namespace sep

#endif // __DER_SETTINGS_H__