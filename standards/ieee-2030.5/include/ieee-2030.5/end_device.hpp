#ifndef __END_DEVICE_H__
#define __END_DEVICE_H__
#include <cstdint>
#include "abstract_device.hpp"
#include "time_type.hpp"
#include "link.hpp"
#include "list_link.hpp"


namespace sep
{
    // Asset container that performs one or more end device functions. 
    // Contains information about individual devices in the network.
    struct EndDevice : AbstractDevice
    {
        sep::TimeType changed_time;
        bool enabled;
        ListLink flow_reservation_request_list_link;
        ListLink flow_reservation_response_list_link;
        ListLink function_set_assignments_list_link;
        uint32_t post_rate;
        Link registration_link;
        ListLink subscription_list_link;
    };
    
} // namespace sep

#endif // __END_DEVICE_H__