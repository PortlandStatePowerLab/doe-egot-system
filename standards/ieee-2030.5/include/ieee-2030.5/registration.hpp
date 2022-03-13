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

        friend bool operator == (const Registration& lhs, const Registration& rhs)
        {
            return
                (lhs.poll_rate == rhs.poll_rate)
                && (lhs.href == rhs.href)
                && (lhs.date_time_registered == rhs.date_time_registered)
                && (lhs.pin == rhs.pin);
        };
    };
    
} // namespace sep

#endif // __REGISTRATION_H__