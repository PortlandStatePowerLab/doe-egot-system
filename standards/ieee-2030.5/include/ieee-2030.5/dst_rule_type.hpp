#ifndef __DST_RULE_TYPE_H__
#define __DST_RULE_TYPE_H__

#include <cstdint>

namespace sep
{
    // Bit map encoded rule from which is calculated the start or end time, 
    // within the current year, to which daylight savings time offset 
    // must be applied.  
    struct DstRuleType 
    {
        enum class Operator : uint8_t
        {
            kDayOfMonth,
            kDayOfWeek,
            kFirstOccurence,
            kSecondOccurence,
            kThirdOccurence,
            kFourthOccurence,
            kFifthOccurence,
            kLastOccurence
        };
        
        uint16_t seconds;
        uint8_t hours;
        uint8_t day_of_the_week;
        uint8_t day_of_the_month;
        Operator op_code;
        uint8_t month;
    };
      
} // namespace sep

#endif // __DST_RULE_TYPE_H__