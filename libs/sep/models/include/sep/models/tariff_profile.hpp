#ifndef __TARIFF_PROFILE_H__
#define __TARIFF_PROFILE_H__
#include "currency_code.hpp"
#include "primacy_type.hpp"
#include "rate_component.hpp"
#include "service_kind.hpp"
#include "simple_types.hpp"

namespace sep {
struct TariffProfileListLink : ListLink {};
struct TariffProfileLink : Link {};

///
/// A schedule of charges; structure that allows the definition of
/// tariff structures such as step (block) and time of use (tier) when
/// used in conjunction with TimeTariffInterval and
/// ConsumptionTariffInterval.
///
struct TariffProfile : IdentifiedObject {
  CurrencyCode currency;
  PowerOfTenMultiplierType price_power_of_ten_multiplier;
  PrimacyType primacy;
  String20 rate_code;
  RateComponentListLink rate_component_list_link;
  ServiceKind service_category_kind;
};
} // namespace sep

#endif // __TARIFF_PROFILE_H__
