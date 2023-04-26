#ifndef __TARIFF_PROFILE_H__
#define __TARIFF_PROFILE_H__
#include "simple_types.hpp"
#include "currency_code.hpp"
#include "primacy_type.hpp"
#include "rate_component.hpp"
#include "service_kind.hpp"

namespace sep{
    struct TariffProfile : IdentifiedObject{
        CurrencyCode currency;
        PowerOfTenMultiplierType price_power_of_ten_multiplier;
        PrimacyType primacy;
        String20 rate_code;
        RateComponentListLink rate_component_list_link;
        ServiceKind service_category_kind;
    };
}

#endif // __TARIFF_PROFILE_H__