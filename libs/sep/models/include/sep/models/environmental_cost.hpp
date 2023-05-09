#ifndef __ENVIRONMENTAL_COST_H__
#define __ENVIRONMENTAL_COST_H__
#include "simple_types.hpp"

namespace sep{
    // Provides alternative or secondary price information for the relevant RateComponent. 
    // Supports jurisdictions that seek to convey the environmental price per unit 
    // of the specified commodity not expressed in currency. Implementers and consumers 
    // can use this attribute to prioritize operations of their HAN devices 
    // (e.g., PEV charging during times of high availability of renewable electricity resources).
    struct EnvironmentalCost{
        enum class CostKindType : UInt8{
            CARBON_DIOXIDE,
            SULFUR_DIOXIDE,
            NITROGEN_OXIDES,
            RENEWABLE_GENERRATION
        };

        UInt32 amount;
        CostKindType cost_kind;
        UInt8 cost_level;
        UInt8 num_cost_levels;
    };
}

#endif // __ENVIRONMENTAL_COST_H__