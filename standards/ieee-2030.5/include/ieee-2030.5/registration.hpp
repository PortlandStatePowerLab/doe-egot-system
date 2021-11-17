#ifndef __REGISTRATION_H__
#define __REGISTRATION_H__
#include <cstdint>
#include "resource.hpp"
#include "time_type.hpp"
#include "pin_type.hpp"

namespace sep
{
    struct Registration : Resource
    {
        TimeType date_time_registered;
        PINType pin;
        uint32_t poll_rate = 900;
    };
    
} // namespace sep

#endif // __REGISTRATION_H__