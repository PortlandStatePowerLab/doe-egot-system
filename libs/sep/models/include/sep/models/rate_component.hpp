#ifndef __RATE_COMPONENT_H__
#define __RATE_COMPONENT_H__
#include "reading_type.hpp"
#include "role_flags_type.hpp"
#include "simple_types.hpp"
#include "time_tariff_interval.hpp"
#include "unit_value_type.hpp"

namespace sep {
struct RateComponentListLink : ListLink {};
struct RateComponentLink : Link {};

///
/// Specifies the applicable charges for a single component of the rate,
/// which could be generation price or consumption price, for example.
///
struct RateComponent : IdentifiedObject {
  ActiveTimeTariffIntervalListLink active_time_tariff_interval;
  UnitValueType flow_rate_end_limit;
  UnitValueType flow_rate_start_limit;
  ReadingTypeLink reading;
  RoleFlagsType role_flag;
  TimeTariffIntervalLink time_tariff_interval;
};
} // namespace sep

#endif // __RATE_COMPONENT_H__
