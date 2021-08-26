#ifndef __DER_UNIT_REF_TYPE_H__
#define __DER_UNIT_REF_TYPE_H__
#include <cstdint>

namespace sep
{
    // Specifies context for interpreting percent values
    enum class DERUnitRefType : uint8_t
    {
        kNA,
        kSetMaxW,
        kSetMaxVar,
        kStatVarAvail,
        kSetEffectiveV,
        kSetMaxChargeRateW,
        kSetMaxDischargeRateW,
        kStatWAvail
    };

};     // namespace sep
#endif // __DER_UNIT_REF_TYPE_H__