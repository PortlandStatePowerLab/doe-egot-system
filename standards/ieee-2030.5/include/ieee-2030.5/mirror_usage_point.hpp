#ifndef __MIRROR_USAGE_POINT_H__
#define __MIRROR_USAGE_POINT_H__
#include <boost/multiprecision/cpp_int.hpp>
#include <vector>
#include "usage_point_base.hpp"
#include "mirror_meter_reading.hpp"
#include "lfdi_type.hpp"

namespace sep
{
    // A parallel to UsagePoint to support mirroring
    struct MirrorUsagePoint : UsagePointBase
    {
        LFDIType device_lfdi;
        MirrorMeterReading mirror_meter_reading;
        uint32_t post_rate;
    };
    
} // namespace sep

#endif // __MIRROR_USAGE_POINT_H__