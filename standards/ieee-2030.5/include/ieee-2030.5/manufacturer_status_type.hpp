#ifndef __MANUFACTURER_STATUS_TYPE_H__
#define __MANUFACTURER_STATUS_TYPE_H__
#include <string>
#include "time_type.hpp"

namespace sep
{
    struct ManufacturerStatusType
    {
        TimeType date_time;
        std::string value;
    };
    
} // namespace sep

#endif // __MANUFACTURER_STATUS_TYPE_H__