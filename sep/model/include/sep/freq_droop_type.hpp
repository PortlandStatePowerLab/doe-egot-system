#ifndef __FREQ_DROOP_TYPE_H__
#define __FREQ_DROOP_TYPE_H__
#include <cstdint>

namespace sep
{
    // Type for Frequency-Droop (Frequency-Watt) operation.
    struct FreqDroopType
    {
        uint32_t dbof;          // over-freq thousandths of Hz
        uint32_t dbuf;          // under-freq thousandths of Hz
        uint16_t kof;           // per-unit change over-freq
        uint16_t kuf;           // per-unit change under-freq
        uint16_t open_loop_tms; // A value of 0 is used to mean no limit
    };
};     // namespace sep
#endif // __FREQ_DROOP_TYPE_H__