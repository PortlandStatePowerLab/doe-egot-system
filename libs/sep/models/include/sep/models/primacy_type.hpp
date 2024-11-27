#ifndef __PRIMACY_TYPE_H__
#define __PRIMACY_TYPE_H__
#include "simple_types.hpp"

namespace sep
{
    enum class PrimacyType : UInt8
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