#ifndef __TIME_CONFIGURATION_H__
#define __TIME_CONFIGURATION_H__

#include "dst_rule_type.hpp"
#include "time_offset_type.hpp"

namespace sep
{
    // Contains attributes related to the configuration of the time service.
    struct TimeConfiguration
    {
        DstRuleType dst_end_rule;
        TimeOffsetType dst_offset;
        DstRuleType dst_start_rule;
        TimeOffsetType tz_offset;
    };
    
} // namespace sep

#endif // __TIME_CONFIGURATION_H__