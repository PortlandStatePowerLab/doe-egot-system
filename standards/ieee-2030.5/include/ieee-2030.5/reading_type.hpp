#ifndef __READING_TYPE_H__
#define __READING_TYPE_H__
#include <cstdint>
#include "resource.hpp"
#include "accumulation_behaviour_type.hpp"
#include "unit_value_type.hpp"
#include "commodity_type.hpp"
#include "data_qualifier_type.hpp"
#include "flow_direction_type.hpp"
#include "kind_type.hpp"
#include "phase_code.hpp"

namespace sep
{
    struct ReadingType : Resource
    {
        AccumulationBehaviourType accumulation_behaviour;
        UnitValueType calorific_value;
        CommodityType commodity;
        UnitValueType conversion_factor;
        DataQualifierType data_qualifier;
        FlowDirectionType flow_direction;
        uint32_t interval_length;
        KindType kind;
        uint8_t max_number_of_intervals;
        uint8_t number_of_consumption_blocks;
        uint8_t number_of_tou_tiers;
        PhaseCode phase;
        PowerOfTenMultiplierType power_of_ten_multiplier;
        uint32_t sub_interval_length;
        uint64_t supply_limit;
        bool tiered_consumption_blocks;
        UomType uom;
    };
    
} // namespace sep

#endif // __READING_TYPE_H__