#ifndef __GPS_LOCATION_TYPE_H__
#define __GPS_LOCATION_TYPE_H__

#include <string>

namespace sep
{
    // Specifies a GPS location, expressed in WGS 84 coordinates
    struct GPSLocationType
    {
        std::string lat;
        std::string lon;
    };
} // namespace sep

#endif // __GPS_LOCATION_TYPE_H__