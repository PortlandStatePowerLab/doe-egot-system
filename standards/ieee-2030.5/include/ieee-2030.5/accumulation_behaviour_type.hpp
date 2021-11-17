#ifndef __ACCUMULATION_BEHAVIOUR_TYPE_H__
#define __ACCUMULATION_BEHAVIOUR_TYPE_H__
#include <cstdint>

namespace sep
{
    enum class AccumulationBehaviourType : uint8_t
    {
        kNA,
        kCumulative,
        kDeltaData,
        kIndicating,
        kSummation,
        kInstantaneous
    };
    
} // namespace sep

#endif // __ACCUMULATION_BEHAVIOUR_TYPE_H__