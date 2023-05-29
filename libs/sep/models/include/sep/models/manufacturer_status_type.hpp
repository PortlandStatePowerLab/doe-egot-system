#ifndef __MANUFACTURER_STATUS_TYPE_H__
#define __MANUFACTURER_STATUS_TYPE_H__
#include "simple_types.hpp"

namespace sep
{
    // DER ManufacturerStatus/value: String data type
    struct ManufacturerStatusType
    {
        TimeType date_time;
        String6 value;
    };
    
} // namespace sep

#endif // __MANUFACTURER_STATUS_TYPE_H__