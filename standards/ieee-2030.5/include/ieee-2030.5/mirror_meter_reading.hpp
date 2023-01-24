#ifndef __MIRROR_METER_READING_H__
#define __MIRROR_METER_READING_H__
#include "meter_reading_base.hpp"
#include "time_type.hpp"
#include "mirror_reading_set.hpp"
#include "reading.hpp"
#include "reading_type.hpp"

namespace sep
{
    // Mimic of MeterReading used for managing mirrors.
    struct MirrorMeterReading : MeterReadingBase
    {
        TimeType last_update_time;
        MirrorReadingSet mirror_reading_set;
        TimeType next_update_time;
        Reading reading;
        ReadingType reading_type;
    };
    
} // namespace sep

#endif // __MIRROR_METER_READING_H__