#ifndef __DEVICE_CATEGORY_TYPE_H__
#define __DEVICE_CATEGORY_TYPE_H__
#include <cstdint>

namespace sep
{
    enum class DeviceCategoryType : uint32_t
    {
        kProgrammableCommunicatingThermostat = 1 << 0,
        kStripHeaters = 1 << 1,
        kBaseboardHeaters = 1 << 2,
        kWaterHeaters = 1 << 3,
        kPoolPump = 1 << 4,
        kSauna = 1 << 5,
        kHotTub = 1 << 6,
        kSmartAppliance = 1 << 7,
        kIrrigationPump = 1 << 8,
        kManagedCommercialIndustrialLoads = 1 << 9,
        kSimpleMiscLoads = 1 << 10,
        kExteriorLighting = 1 << 11,
        kInteriorLighting = 1 << 12,
        kLoadControlSwitch = 1 << 13,
        kEnergyManagementSystem = 1 << 14,
        kSmartEnergyModule = 1 << 15,
        kElectricVehicle = 1 << 16,
        kEVSE = 1 << 17,
        KVirtualMixedDER = 1 << 18,
        kReciprocatingEngine = 1 << 19,
        kFuelCell = 1 << 20,
        kPhotovoltaicSystem= 1 << 21,
        kCombinedHeatAndPower = 1 << 22,
        kCombinedPVAndStorage = 1 << 23,
        kOtherGenerationSystem = 1 << 24,
        kOtherStorageSystem = 1 << 25
    };
};     // namespace sep
#endif // __DEVICE_CATEGORY_TYPE_H__