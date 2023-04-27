#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

#include "simple_types.hpp"
#include "subscribable_resource.hpp"
#include "locale_type.hpp"
#include "power_configuration.hpp"
#include "price_response_configuration.hpp"
#include "time_configuration.hpp"
#include "simple_types.hpp"

namespace sep
{
    struct ConfigurationLink : Link {};

    // This resource contains various settings to control 
    // the operation of the device.
    struct Configuration : SubscribableResource
    {
        LocaleType current_locale;
        PowerConfiguration power_configuration;
        PriceResponseCfgListLink price_response_configuration;
        TimeConfiguration time_configuration;
        String32 user_device_name;
        UInt32 poll_rate;
    };
    
} // namespace sep

#endif // __CONFIGURATION_H__