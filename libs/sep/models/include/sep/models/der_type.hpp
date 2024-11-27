#ifndef __DER_TYPE_H__
#define __DER_TYPE_H__
#include "simple_types.hpp"

namespace sep
{
    enum class DERType : UInt8
    {
        kNA,
        kVirtual,
        kReciprocatingEngine,
        kFuelCell,
        kPhotovoltaicSystem,
        kCombinedHeatAndPower,
        kOtherStorageSystem,
        kElectricVehicle,
        kEVSE,
        kCombinedStorageAndPV
    };
    
} // namespace sep

#endif // __DER_TYPE_H__