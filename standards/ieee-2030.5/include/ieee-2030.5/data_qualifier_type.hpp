#ifndef __DATA_QUALIFIER_TYPE_H__
#define __DATA_QUALIFIER_TYPE_H__
#include <cstdint>

namespace sep
{
    enum class DataQualifierType : uint8_t
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