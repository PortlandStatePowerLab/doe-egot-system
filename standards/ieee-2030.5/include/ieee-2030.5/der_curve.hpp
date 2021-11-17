#ifndef __DER_CURVE_H__
#define __DER_CURVE_H__
#include <cstdint>
#include "identified_object.hpp"
#include "time_type.hpp"
#include "curve_data.hpp"
#include "der_curve_type.hpp"
#include "per_cent.hpp"
#include "power_of_ten_multiplier_type.hpp"
#include "der_unit_ref_type.hpp"

namespace sep
{
    struct DERCurve : IdentifiedObject
    {
        bool autonomous_vref_enable;
        uint32_t autonomous_vref_time_constant;
        TimeType creation_time;
        CurveData curve_data;
        DERCurveType curve_type;
        uint16_t open_loop_tms;
        uint16_t ramp_dec_tms;
        uint16_t ramp_inc_tms;
        uint16_t ramp_pt1_tms;
        PerCent vref;
        PowerOfTenMultiplierType x_multiplier;
        PowerOfTenMultiplierType y_multiplier;
        DERUnitRefType y_ref_type;

    };
    
} // namespace sep

#endif // __DER_CURVE_H__