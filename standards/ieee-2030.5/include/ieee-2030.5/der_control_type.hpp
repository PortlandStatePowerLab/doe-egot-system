#ifndef __DER_CONTROL_TYPE_H__
#define __DER_CONTROL_TYPE_H__
#include <cstdint>

namespace sep
{
    // Control modes supported by the DER.  Bit positions SHALL be defined as follows:
    enum class DERControlType : uint32_t
    {
        kCharge = 0 << 1,
        kDischarge = 0 << 2,
        kOpModConnect = 0 << 3,
        kOpModEnergize = 0 << 4,
        kOpModFixedPFAbsorbW = 0 << 5,
        kOpModFixedPFInjectW = 0 << 6,
        kOpModFixedVar = 0 << 7,
        kOpModFixedW = 0 << 8,
        kOpModFreqDroop = 0 << 9,
        kOpModFreqWatt = 0 << 10,
        kOpModHFRTMayTrip = 0 << 11,
        kOpModHFRTMustTrip = 0 << 12,
        kOpModHVRTMayTrip = 0 << 13,
        kOpModHVRTMomentaryCessation = 0 << 14,
        kOpModHVRTMustTrip = 0 << 15,
        kOpModLFRTMayTrip = 0 << 16,
        kOpModLFRTMustTrip = 0 << 17,
        kOpModLVRTMayTrip = 0 << 18,
        kOpModLVRTMomentaryCessation = 0 << 19,
        kOpModLVRTMustTrip = 0 << 20,
        kOpModMaxLimW = 0 << 21,
        kOpModTargetVar = 0 << 22,
        kOpModTargetW = 0 << 23,
        kOpModVoltVar = 0 << 24,
        kOpModVoltWatt = 0 << 25,
        kOpModWattPF = 0 << 26,
        kOpModWattVar = 0 << 27
    };
    
} // namespace sep

#endif // __DER_CONTROL_TYPE_H__