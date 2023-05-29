#ifndef __CONSUMPTION_BLOCK_H__
#define __CONSUMPTION_BLOCK_H__
#include "simple_types.hpp"

namespace sep
{
    // Indicates the consumption block related to the reading. 
    // REQUIRED if ReadingType numberOfConsumptionBlocks is non-zero. 
    // If not specified, is assumed to be "0 - N/A".
    enum class ConsumptionBlock : UInt8
    {
        kNA,
        kBlock1,
        kBlock2,
        kBlock3,
        kBlock4,
        kBlock5,
        kBlock6,
        kBlock7,
        kBlock8,
        kBlock9,
        kBlock10,
        kBlock11,
        kBlock12,
        kBlock13,
        kBlock14,
        kBlock15,
        kBlock16,
    };
    
} // namespace sep

#endif // __CONSUMPTION_BLOCK_H__