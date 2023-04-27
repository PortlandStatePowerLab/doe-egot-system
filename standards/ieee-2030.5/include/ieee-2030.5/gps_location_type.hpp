#ifndef __GPS_LOCATION_TYPE_H__
#define __GPS_LOCATION_TYPE_H__

#include "simple_types.hpp"

namespace sep
{
    // Specifies a GPS location, expressed in WGS 84 coordinates
    struct GPSLocationType
    {
        String32 lat;
        String32 lon;
    };
} // namespace sep

#endif // __GPS_LOCATION_TYPE_H__