#ifndef __FREQ_DROOP_TYPE_H__
#define __FREQ_DROOP_TYPE_H__
#include "simple_types.hpp"

namespace sep {
///
/// Type for Frequency-Droop (Frequency-Watt) operation.
///
struct FreqDroopType {
  UInt32 dbof;          // over-freq thousandths of Hz
  UInt32 dbuf;          // under-freq thousandths of Hz
  UInt16 kof;           // per-unit change over-freq
  UInt16 kuf;           // per-unit change under-freq
  UInt16 open_loop_tms; // A value of 0 is used to mean no limit
};
};     // namespace sep
#endif // __FREQ_DROOP_TYPE_H__
