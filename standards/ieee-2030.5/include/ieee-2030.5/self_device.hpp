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

        friend bool operator == (const SelfDevice& lhs, const SelfDevice& rhs)
        {
            return 
                (lhs.configuration_link.href == rhs.configuration_link.href)
                & (lhs.der_list_link.all == rhs.der_list_link.all)
                & (lhs.der_list_link.href == rhs.der_list_link.href)
                & (lhs.device_category == rhs.device_category)
                & (lhs.device_information_link.href == rhs.device_information_link.href)
                & (lhs.device_status_link.href == rhs.device_status_link.href)
                & (lhs.file_status_link.href == rhs.file_status_link.href)
                & (lhs.href == rhs.href)
                & (lhs.ip_interface_list_link.all == rhs.ip_interface_list_link.all)
                & (lhs.ip_interface_list_link.href == rhs.ip_interface_list_link.href)
                & (lhs.lfdi == rhs.lfdi)
                & (lhs.load_shed_availability_list_link.all == rhs.load_shed_availability_list_link.all)
                & (lhs.load_shed_availability_list_link.href == rhs.load_shed_availability_list_link.href)
                & (lhs.log_event_list_link.all == rhs.log_event_list_link.all)
                & (lhs.log_event_list_link.href == rhs.log_event_list_link.href)
                & (lhs.poll_rate == rhs.poll_rate)
                & (lhs.power_status_link.href == rhs.power_status_link.href)
                & (lhs.sfdi == rhs.sfdi)
                & (lhs.subscribable == rhs.subscribable);
        };
    };
    
} // namespace sep

#endif // __SELF_DEVICE_H__