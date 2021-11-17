#ifndef __COMMODITY_TYPE_H__
#define __COMMODITY_TYPE_H__
#include <cstdint>

namespace sep
{
    enum class CommodityType : uint8_t
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