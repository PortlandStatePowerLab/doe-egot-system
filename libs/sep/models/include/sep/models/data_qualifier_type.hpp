#ifndef __DATA_QUALIFIER_TYPE_H__
#define __DATA_QUALIFIER_TYPE_H__
#include "simple_types.hpp"

namespace sep
{
    enum class DataQualifierType : UInt8
    {
        kNA,
        kAverage = 2,
        kMaximum = 8,
        kMinimum = 9,
        kNormal = 12,
        kStandardDeviationOfPopulation = 29,
        kStandardDeviationOfSample = 30
    };

} // namespace sep

#endif // __DATA_QUALIFIER_TYPE_H__