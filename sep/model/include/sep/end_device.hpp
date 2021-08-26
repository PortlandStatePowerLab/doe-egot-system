#ifndef __END_DEVICE_H__
#define __END_DEVICE_H__
#include <string>
#include <cstdint>
#include "abstract_device.hpp"
#include "time_type.hpp"


namespace sep
{
    // Asset container that performs one or more end device functions. 
    // Contains information about individual devices in the network.
    struct EndDevice : AbstractDevice
    {
        sep::TimeType changed_time;
        bool enabled;
        std::string flow_reservation_request_list_link;
        std::string flow_reservation_response_list_link;
        std::string function_set_assignments_list_link;
        uint32_t post_rate;
        std::string registration_link;
        std::string subscription_list_link;
    };
    
} // namespace sep

#endif // __END_DEVICE_H__