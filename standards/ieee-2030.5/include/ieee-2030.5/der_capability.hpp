#ifndef __DER_CAPABILITY_H__
#define __DER_CAPABILITY_H__
#include <cstdint>
#include "resource.hpp"
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

namespace sep
{
    // Distributed energy resource type and nameplate ratings.
    struct DERCapability : Resource
    {
        enum class AbnormalCategory : uint8_t
        {
            kNotSpecified,
            kI,
            kII,
            kIII
        };

        enum class NormalCategory : uint8_t
        {
            kNotSpecified,
            kA,
            kB
        };

        DERControlType modes_supported;
        AbnormalCategory rtg_abnormal_category;
        CurrentRMS rtg_max_a;
        AmpereHour rtg_max_ah;
        ApparentPower rtg_max_charge_rate_va;
        ActivePower rtg_max_charge_rate_w;
        ApparentPower rtg_max_discharge_rate_va;
        ActivePower rtg_max_discharge_rate_w;
        VoltageRMS rtg_max_v;
        ApparentPower rtg_max_va;
        ReactivePower rtg_max_var;
        ReactivePower rtg_max_var_neg;
        ActivePower rtg_max_w;
        WattHour rtg_max_wh;
        PowerFactor rtg_min_pf_over_excited;
        VoltageRMS rtg_min_v;
        NormalCategory rtg_normal_category;
        PowerFactor rtg_over_excited_pf;
        ActivePower rtg_over_excited_w;
        ReactivePower rtg_reactive_susceptance;
        PowerFactor rtg_under_excited_pf;
        ActivePower rtg_under_excited_w;
        VoltageRMS rtg_v_nom;
        DERType type;
    };
    
} // namespace sep

#endif // __DER_CAPABILITY_H__