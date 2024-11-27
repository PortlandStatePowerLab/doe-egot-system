#ifndef __READING_TYPE_H__
#define __READING_TYPE_H__
#include "accumulation_behaviour_type.hpp"
#include "commodity_type.hpp"
#include "data_qualifier_type.hpp"
#include "flow_direction_type.hpp"
#include "kind_type.hpp"
#include "phase_code.hpp"
#include "simple_types.hpp"
#include "unit_value_type.hpp"

namespace sep {
struct ReadingTypeLink : Link {};
///
/// Type of data conveyed by a specific Reading. See IEC 61968 Part 9 Annex C
/// for full definitions of these values.
///
struct ReadingType : Resource {
  AccumulationBehaviourType accumulation_behaviour;
  UnitValueType calorific_value;
  CommodityType commodity;
  UnitValueType conversion_factor;
  DataQualifierType data_qualifier;
  FlowDirectionType flow_direction;
  UInt32 interval_length;
  KindType kind;
  UInt8 max_number_of_intervals;
  UInt8 number_of_consumption_blocks;
  UInt8 number_of_tou_tiers;
  PhaseCode phase;
  PowerOfTenMultiplierType power_of_ten_multiplier;
  UInt32 sub_interval_length;
  UInt48 supply_limit;
  bool tiered_consumption_blocks;
  UomType uom;
};

} // namespace sep

#endif // __READING_TYPE_H__
