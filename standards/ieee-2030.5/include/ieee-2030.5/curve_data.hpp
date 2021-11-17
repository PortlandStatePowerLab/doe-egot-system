#ifndef __CURVE_DATA_H__
#define __CURVE_DATA_H__
#include <cstdint>

namespace sep
{
    // Data point values for defining a curve or schedule
    struct CurveData 
    {
        bool excitation;
        int32_t x_value;
        int32_t y_value;
    };
    
} // namespace sep

#endif // __CURVE_DATA_H__