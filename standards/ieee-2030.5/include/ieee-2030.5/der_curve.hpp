#ifndef __DER_CURVE_H__
#define __DER_CURVE_H__
#include "simple_types.hpp"
#include "curve_data.hpp"
#include "der_curve_type.hpp"
#include "per_cent.hpp"
#include "der_unit_ref_type.hpp"

namespace sep
{
    struct DERCurveListLink : ListLink {};
    struct DERCurveLink : Link {};

    // DER related curves such as Volt-Var mode curves. Relationship between 
    // an independent variable (X-axis) and a dependent variable (Y-axis).
    struct DERCurve : IdentifiedObject
    {
        bool autonomous_vref_enable;
        UInt32 autonomous_vref_time_constant;
        TimeType creation_time;
        CurveData curve_data;
        DERCurveType curve_type;
        UInt16 open_loop_tms;
        UInt16 ramp_dec_tms;
        UInt16 ramp_inc_tms;
        UInt16 ramp_pt1_tms;
        PerCent vref;
        PowerOfTenMultiplierType x_multiplier;
        PowerOfTenMultiplierType y_multiplier;
        DERUnitRefType y_ref_type;
    };
    
} // namespace sep

#endif // __DER_CURVE_H__