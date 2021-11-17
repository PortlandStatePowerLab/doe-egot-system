#ifndef __STATE_OF_CHARGE_STATUS_TYPE_H__
#define __STATE_OF_CHARGE_STATUS_TYPE_H__
#include "time_type.hpp"
#include "per_cent.hpp"

namespace sep
{
    struct StateOfChargeStatusType
    {
        TimeType date_time;
        PerCent value;
    };
    
} // namespace sep

#endif // __STATE_OF_CHARGE_STATUS_TYPE_H__