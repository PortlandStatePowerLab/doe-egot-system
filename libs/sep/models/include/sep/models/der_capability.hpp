#ifndef __DER_CAPABILITY_H__
#define __DER_CAPABILITY_H__
#include "active_power.hpp"
#include "ampere_hour.hpp"
#include "apparent_power.hpp"
#include "current_rms.hpp"
#include "der_control_type.hpp"
#include "der_type.hpp"
#include "power_factor.hpp"
#include "reactive_power.hpp"
#include "simple_types.hpp"
#include "voltage_rms.hpp"
#include "watt_hour.hpp"
#include <boost/optional.hpp>

namespace sep {
struct DERCapabilityLink : Link {};

///
/// Distributed energy resource type and nameplate ratings.
///
struct DERCapability : Resource {
  enum class AbnormalCategory : UInt8 { kNotSpecified, kI, kII, kIII };

  enum class NormalCategory : UInt8 { kNotSpecified, kA, kB };

  DERControlType modes_supported;
  ActivePower rtg_max_w;
  DERType type;
  boost::optional<AbnormalCategory> rtg_abnormal_category;
  boost::optional<CurrentRMS> rtg_max_a;
  boost::optional<AmpereHour> rtg_max_ah;
  boost::optional<ApparentPower> rtg_max_charge_rate_va;
  boost::optional<ActivePower> rtg_max_charge_rate_w;
  boost::optional<ApparentPower> rtg_max_discharge_rate_va;
  boost::optional<ActivePower> rtg_max_discharge_rate_w;
  boost::optional<VoltageRMS> rtg_max_v;
  boost::optional<ApparentPower> rtg_max_va;
  boost::optional<ReactivePower> rtg_max_var;
  boost::optional<ReactivePower> rtg_max_var_neg;
  boost::optional<WattHour> rtg_max_wh;
  boost::optional<PowerFactor> rtg_min_pf_over_excited;
  boost::optional<PowerFactor> rtg_min_pf_under_excited;
  boost::optional<VoltageRMS> rtg_min_v;
  boost::optional<NormalCategory> rtg_normal_category;
  boost::optional<PowerFactor> rtg_over_excited_pf;
  boost::optional<ActivePower> rtg_over_excited_w;
  boost::optional<ReactivePower> rtg_reactive_susceptance;
  boost::optional<PowerFactor> rtg_under_excited_pf;
  boost::optional<ActivePower> rtg_under_excited_w;
  boost::optional<VoltageRMS> rtg_v_nom;
};

} // namespace sep

#endif // __DER_CAPABILITY_H__
