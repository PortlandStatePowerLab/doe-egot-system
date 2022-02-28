#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

#include <cstdint>
#include <string>
#include "subscribable_resource.hpp"
#include "locale_type.hpp"
#include "power_configuration.hpp"
#include "time_configuration.hpp"

namespace sep
{
    // This resource contains various settings to control 
    // the operation of the device.
    struct Configuration : SubscribableResource
    {
        LocaleType current_locale;
        PowerConfiguration power_configuration;
        TimeConfiguration time_configuration;
        std::string user_device_name;
        uint32_t poll_rate;
    };
    
} // namespace sep

#endif // __CONFIGURATION_H__