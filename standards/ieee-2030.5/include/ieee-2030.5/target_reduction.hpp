#ifndef __TARGET_REDUCTION_H__
#define __TARGET_REDUCTION_H__
#include <cstdint>

namespace sep
{
    // The unit types defined for end device control target reductions
    enum class UnitType : uint8_t
    {
        kkWh,
        kkW,
        kWatts,
        KCubicMeters,
        kCubicFeet,
        kUSGallons,
        kImperialGallons,
        kBTUs,
        kLiters,
        kkPAGuage,
        kkPAAbsolute,
        kMegaJoule,
        kUnitless
    };

    // The TargetReduction object is used by a Demand Response service provider
    // to provide a RECOMMENDED threshold that a device/premises should maintain
    // its consumption below.
    //
    // For example, a service provider can provide a RECOMMENDED threshold of
    // some kWh for a 3-hour event. This means that the device/premises would
    // maintain its consumption below the specified limit for the specified period.
    struct TargetReduction
    {
        sep::UnitType unit_type;
        uint16_t value;
    };
};     // namespace sep
#endif // __TARGET_REDUCTION_H__