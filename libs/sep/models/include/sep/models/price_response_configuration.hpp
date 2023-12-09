#ifndef __PRICE_RESPONSE_CONFIGURATION_H__
#define __PRICE_RESPONSE_CONFIGURATION_H__
#include "rate_component.hpp"
#include "simple_types.hpp"

namespace sep {
struct PriceResponseCfgListLink : ListLink {};
struct PriceResponseCfgLink : Link {};

///
/// Configuration data that specifies how price responsive devices SHOULD
/// respond to price changes while acting upon a given RateComponent.
///
struct PriceResponseCfg : Resource {
  Int32 consume_threshold;
  Int32 max_reduction_threshold;
  RateComponentLink rate_component;
};
} // namespace sep

#endif // __PRICE_RESPONSE_CONFIGURATION_H__
