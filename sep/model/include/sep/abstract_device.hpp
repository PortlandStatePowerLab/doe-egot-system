#ifndef __ABSTRACT_DEVICE_H__
#define __ABSTRACT_DEVICE_H__
#include <string>
#include "subscribable_resource.hpp"
#include "device_category_type.hpp"

namespace sep
{
    // The EndDevice providing the resources available within the DeviceCapabilities.
    struct AbstractDevice : SubscribableResource
    {
        std::string configuration_link;
        std::string der_list_link;
        sep::DeviceCategoryType device_category;
        std::string device_information_link;
        std::string device_status_link;
        std::string file_status_link;
        std::string ip_interface_list_link;
        std::string lfdi;
        std::string load_shed_availability_list_link;
        std::string log_event_list_link;
        std::string power_status_link;
        uint8_t sfdi; 
    };
        
} // namespace sep

#endif // __ABSTRACT_DEVICE_H__