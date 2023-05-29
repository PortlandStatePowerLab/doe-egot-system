#ifndef __DER_CURVE_TYPE_H__
#define __DER_CURVE_TYPE_H__
#include "simple_types.hpp"

namespace sep
{
    enum class DERCurveType : UInt8
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