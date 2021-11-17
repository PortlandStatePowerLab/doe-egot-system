#ifndef __READING_BASE_H__
#define __READING_BASE_H__
#include "resource.hpp"
#include "consumption_block.hpp"
#include "date_time_interval.hpp"
#include "tou_type.hpp"

namespace sep
{
    // Specific value measured by a meter or other asset. 
    // ReadingBase is abstract, used to define the elements 
    // common to Reading and IntervalReading.
    struct ReadingBase : Resource
    {
        // List of codes indicating the quality of the reading, using specification:
        enum class QualityFlags : uint16_t
        {
            kValid = 1 << 0,
            kManuallyEdited = 1 << 1,
            kEstimatedUsingReferenceDay = 1 << 2,
            kEstimatedUsingLinearInterpolation = 1 << 3,
            kQuestionable = 1 << 4,
            kDerived = 1 << 5,
            kDerived = 1 << 6
        };

        ConsumptionBlock consumption_block;
        QualityFlags quality_flags;
        DateTimeInterval time_period;
        TOUType tou_tier;
        uint64_t value;
    };
    
} // namespace sep

#endif // __READING_BASE_H__