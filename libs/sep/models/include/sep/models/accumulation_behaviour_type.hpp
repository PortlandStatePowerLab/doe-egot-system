#ifndef __ACCUMULATION_BEHAVIOUR_TYPE_H__
#define __ACCUMULATION_BEHAVIOUR_TYPE_H__
#include "simple_types.hpp"

namespace sep
{
    enum class AccumulationBehaviourType : UInt8
    {
        kNA,
        kCumulative = 3,
        kDeltaData = 4,
        kIndicating = 6,
        kSummation = 9,
        kInstantaneous = 12
    };
    
} // namespace sep

#endif // __ACCUMULATION_BEHAVIOUR_TYPE_H__