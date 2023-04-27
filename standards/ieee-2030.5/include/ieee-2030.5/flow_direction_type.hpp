#ifndef __FLOW_DIRECTION_TYPE_H__
#define __FLOW_DIRECTION_TYPE_H__
#include "simple_types.hpp"

namespace sep
{
    enum class FlowDirectionType : UInt8
    {
        kNA,
        kForward,
        kReverse = 19
    };
} // namespace sep

#endif // __FLOW_DIRECTION_TYPE_H__