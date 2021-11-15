#ifndef __SUBSCRIBABLE_TYPE_H__
#define __SUBSCRIBABLE_TYPE_H__
#include <cstdint>

namespace sep
{
    enum class SubscribableType : uint8_t
    {
        kNone,
        kNonConditional,
        kConditional,
        kBoth
    };
};     // namespace sep
#endif // __SUBSCRIBABLE_TYPE_H__