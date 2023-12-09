#ifndef __MIRROR_USAGE_POINT_H__
#define __MIRROR_USAGE_POINT_H__
#include "mirror_meter_reading.hpp"
#include "simple_types.hpp"
#include "usage_point_base.hpp"
#include <vector>

namespace sep {
struct MirrorUsagePointListLink : ListLink {};
struct MirrorUsagePointLink : Link {};

///
/// A parallel to UsagePoint to support mirroring
///
struct MirrorUsagePoint : UsagePointBase {
  HexBinary160 device_lfdi;
  MirrorMeterReading mirror_meter_reading;
  UInt32 post_rate;
};

struct MirrorUsagePointList : List {
  std::vector<MirrorUsagePoint> mirror_usage_points;
  UInt32 poll_rate;
};

} // namespace sep

#endif // __MIRROR_USAGE_POINT_H__
