#ifndef __CONSUMPTION_TARIFF_INTERVAL_H__
#define __CONSUMPTION_TARIFF_INTERVAL_H__
#include "environmental_cost.hpp"
#include "simple_types.hpp"

namespace sep {
struct ConsumptionTariffIntervalListLink : ListLink {};
struct ConsumptionTariffIntervalLink : Link {};

///
/// One of a sequence of thresholds defined in terms of consumption quantity
/// of a service such as electricity, water, gas, etc. It defines the steps or
/// blocks in a step tariff structure, where startValue simultaneously defines
/// the entry value of this step and the closing value of the previous step.
/// Where consumption is greater than startValue, it falls within this block
/// and where consumption is less than or equal to startValue, it falls within
/// one of the previous blocks.
///
struct ConsumptionTariffInterval : Resource {
  enum class ConsumptionBlockType : UInt8 {
    BLOCK1 = 1,
    BLOCK2,
    BLOCK3,
    BLOCK4,
    BLOCK5,
    BLOCK6,
    BLOCK7,
    BLOCK8,
    BLOCK9,
    BLOCK10,
    BLOCK11,
    BLOCK12,
    BLOCK13,
    BLOCK14,
    BLOCK15,
    BLOCK16,
  };

  ConsumptionBlockType consumption_block;
  EnvironmentalCost environmental_cost;
  Int32 price;
  UInt48 startValue;
};
} // namespace sep

#endif // __CONSUMPTION_TARIFF_INTERVAL_H__
