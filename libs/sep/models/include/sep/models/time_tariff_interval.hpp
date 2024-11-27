#ifndef __TIME_TARIFF_INTERVAL_H__
#define __TIME_TARIFF_INTERVAL_H__
#include "consumption_tariff_interval.hpp"
#include "randomizable_event.hpp"
#include "simple_types.hpp"
#include "tou_type.hpp"

namespace sep {
struct ActiveTimeTariffIntervalListLink : ListLink {};
struct ActiveTimeTariffIntervalLink : Link {};
struct TimeTariffIntervalListLink : ListLink {};
struct TimeTariffIntervalLink : Link {};

///
/// Describes the time-differentiated portion of the RateComponent,
/// if applicable, and provides the ability to specify multiple time intervals,
/// each with its own consumption-based components and other attributes.
///
struct TimeTariffInterval : RandomizableEvent {
  ConsumptionTariffIntervalListLink consumption_tariff_interval;
  TOUType tou_tier;
};
} // namespace sep

#endif // __TIME_TARIFF_INTERVAL_H__
