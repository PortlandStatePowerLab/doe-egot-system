#ifndef __FLOW_DIRECTION_TYPE_H__
#define __FLOW_DIRECTION_TYPE_H__
#include <cstdint>

namespace sep
{
    enum class FlowDirectionType : uint8_t
    {
        kNA,
        kForward,
        kReverse = 19
    };
} // namespace sep

#endif // __FLOW_DIRECTION_TYPE_H__