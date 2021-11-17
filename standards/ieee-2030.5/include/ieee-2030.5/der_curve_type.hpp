#ifndef __DER_CURVE_TYPE_H__
#define __DER_CURVE_TYPE_H__
#include <cstdint>

namespace sep
{
    enum class DERCurveType : uint8_t
    {
        kOpModFreqWatt,
        kOpModHFRTMayTrip,
        kOpModHFRTMustTrip,
        kOpModHVRTMayTrip,
        kOpModHVRTMomentaryCessation,
        kOpModHVRTMustTrip,
        kOpModLFRTMayTrip,
        kOpModLFRTMustTrip,
        kOpModLVRTMayTrip,
        kOpModLVRTMomentaryCessation,
        kOpModLVRTMustTrip,
        kOpModVoltVar,
        kOpModVoltWatt,
        kOpModWattPF,
        kOpModWattVar
    };
    
} // namespace sep

#endif // __DER_CURVE_TYPE_H__