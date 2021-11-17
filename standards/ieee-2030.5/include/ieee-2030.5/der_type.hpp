#ifndef __DER_TYPE_H__
#define __DER_TYPE_H__
#include <cstdint>

namespace sep
{
    enum class DERType : uint8_t
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