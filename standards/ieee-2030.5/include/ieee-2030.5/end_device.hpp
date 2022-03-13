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

        friend bool operator == (const EndDevice& lhs, const EndDevice& rhs)
        {
            return
                (lhs.changed_time == rhs.changed_time)
                && (lhs.configuration_link.href == rhs.configuration_link.href)
                && (lhs.der_list_link.all == rhs.der_list_link.all)
                && (lhs.der_list_link.href == rhs.der_list_link.href)
                && (lhs.device_category == rhs.device_category)
                && (lhs.device_information_link.href == rhs.device_information_link.href)
                && (lhs.device_status_link.href == rhs.device_status_link.href)
                && (lhs.enabled == rhs.enabled)
                && (lhs.file_status_link.href == rhs.file_status_link.href)
                && (lhs.flow_reservation_request_list_link.all == rhs.flow_reservation_request_list_link.all)
                && (lhs.flow_reservation_request_list_link.href == rhs.flow_reservation_request_list_link.href)
                && (lhs.flow_reservation_response_list_link.all == rhs.flow_reservation_response_list_link.all)
                && (lhs.flow_reservation_response_list_link.href == rhs.flow_reservation_response_list_link.href)
                && (lhs.function_set_assignments_list_link.all == rhs.function_set_assignments_list_link.all)
                && (lhs.function_set_assignments_list_link.href == rhs.function_set_assignments_list_link.href)
                && (lhs.href == rhs.href)
                && (lhs.ip_interface_list_link.all == rhs.ip_interface_list_link.all)
                && (lhs.ip_interface_list_link.href == rhs.ip_interface_list_link.href)
                && (lhs.lfdi == rhs.lfdi)
                && (lhs.load_shed_availability_list_link.all == rhs.load_shed_availability_list_link.all)
                && (lhs.load_shed_availability_list_link.href == rhs.load_shed_availability_list_link.href)
                && (lhs.log_event_list_link.all == rhs.log_event_list_link.all)
                && (lhs.log_event_list_link.href == rhs.log_event_list_link.href)
                && (lhs.post_rate == rhs.post_rate)
                && (lhs.power_status_link.href == rhs.power_status_link.href)
                && (lhs.registration_link.href == rhs.registration_link.href)
                && (lhs.sfdi == rhs.sfdi)
                && (lhs.subscribable == rhs.subscribable)
                && (lhs.subscription_list_link.all == rhs.subscription_list_link.all)
                && (lhs.subscription_list_link.href == rhs.subscription_list_link.href);
        };
    };
    
} // namespace sep

#endif // __END_DEVICE_H__