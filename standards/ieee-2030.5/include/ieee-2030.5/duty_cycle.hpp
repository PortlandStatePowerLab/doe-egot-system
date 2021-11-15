#ifndef __DUTY_CYCLE_H__
#define __DUTY_CYCLE_H__
#include <cstdint>

namespace sep
{
    // Duty cycle control is a device specific issue and is managed by the device.
    // The duty cycle of the device under control should span the shortest practical
    // time period in accordance with the nature of the device under control and the
    // intent of the request for demand reduction.  The default factory setting SHOULD
    // be three minutes for each 10% of duty cycle.  This indicates that the default
    // time period over which a duty cycle is applied is 30 minutes, meaning a 10% duty
    // cycle would cause a device to be ON for 3 minutes.
    // The “off state” SHALL precede the “on state”.
    struct DutyCycle
    {
        uint8_t normal_value;
    };        
} // namespace sep

#endif // __DUTY_CYCLE_H__