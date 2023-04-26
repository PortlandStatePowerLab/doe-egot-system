#ifndef __MIRROR_USAGE_POINT_H__
#define __MIRROR_USAGE_POINT_H__
#include "simple_types.hpp"
#include "usage_point_base.hpp"
#include "mirror_meter_reading.hpp"

namespace sep
{
    struct MirrorUsagePointListLink : ListLink {};
    struct MirrorUsagePointLink : Link {};
    
    // A parallel to UsagePoint to support mirroring
    struct MirrorUsagePoint : UsagePointBase
    {
        HexBinary160 device_lfdi;
        MirrorMeterReading mirror_meter_reading;
        UInt32 post_rate;
    };
    
} // namespace sep

#endif // __MIRROR_USAGE_POINT_H__