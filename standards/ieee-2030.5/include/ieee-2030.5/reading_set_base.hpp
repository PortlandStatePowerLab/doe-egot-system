#ifndef __READING_SET_BASE_H__
#define __READING_SET_BASE_H__
#include "simple_types.hpp"
#include "date_time_interval.hpp"

namespace sep
{
    // A set of Readings of the ReadingType indicated by the parent MeterReading. 
    // ReadingBase is abstract, used to define the elements common to ReadingSet 
    // and IntervalBlock.</xs:documentation>
    struct ReadingSetBase : IdentifiedObject
    {
        DateTimeInterval time_period;
    };
    
} // namespace sep

#endif // __READING_SET_BASE_H__