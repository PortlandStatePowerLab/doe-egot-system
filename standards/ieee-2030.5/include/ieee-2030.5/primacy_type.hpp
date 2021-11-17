#ifndef __PRIMACY_TYPE_H__
#define __PRIMACY_TYPE_H__
#include <cstdint>

namespace sep
{
    enum class PrimacyType : uint8_t
    {
        kInHomeEnergyManagementSystem,
        kContractededPremisesServiceProvider,
        kNonContractualServiceProvider,
        kReserved = 3,
        kUserDefined = 65,
        kReserved2 = 192
    };
    
} // namespace sep

#endif // __PRIMACY_TYPE_H__