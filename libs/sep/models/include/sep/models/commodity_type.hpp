#ifndef __COMMODITY_TYPE_H__
#define __COMMODITY_TYPE_H__
#include "simple_types.hpp"

namespace sep
{
    enum class CommodityType : UInt8
    {
        kNA,
        kElectricitySecondaryMeterValue,
        kElectricityPrimaryMeterValue,
        kAir = 4,
        kNaturalGas = 7,
        kPropane,
        kPortableWater,
        kSteam,
        kWasteWater,
        kHeatingFluid,
        kCoolingFluid
    };

} // namespace sep

#endif // __COMMODITY_TYPE_H__