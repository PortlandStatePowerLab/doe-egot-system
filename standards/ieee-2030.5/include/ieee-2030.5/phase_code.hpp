#ifndef __PHASE_CODE_H__
#define __PHASE_CODE_H__
#include <cstdint>

namespace sep
{
    enum class PhaseCode : uint8_t
    {
        kNA,
        kC = 32,
        kCN = 33,
        kCA = 40,
        kB = 64,
        kBN = 65,
        kBC = 66,
        kA = 128,
        kAN = 129,
        kAB = 132,
        kABC = 224
    };

} // namespace sep

#endif // __PHASE_CODE_H__