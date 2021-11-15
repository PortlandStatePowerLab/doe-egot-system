#ifndef __SELF_DEVICE_H__
#define __SELF_DEVICE_H__
#include <cstdint>
#include "abstract_device.hpp"

namespace sep
{
    // The EndDevice providing the resources available within the DeviceCapabilities.
    struct SelfDevice : AbstractDevice
    {
        uint32_t poll_rate = 900;
    };
    
} // namespace sep

#endif // __SELF_DEVICE_H__