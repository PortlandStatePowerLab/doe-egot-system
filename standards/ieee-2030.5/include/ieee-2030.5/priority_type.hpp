#ifndef __PRIORITY_TYPE_H__
#define __PRIORITY_TYPE_H__
#include "simple_types.hpp"

namespace sep{
    enum class PriorityType : UInt8{
        LOW,
        NORMAL,
        HIGH,
        CRITICAL
    };
}

#endif // __PRIORITY_TYPE_H__