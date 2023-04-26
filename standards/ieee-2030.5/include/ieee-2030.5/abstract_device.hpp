#ifndef __ABSTRACT_DEVICE_H__
#define __ABSTRACT_DEVICE_H__
#include <string>
#include <boost/multiprecision/cpp_int.hpp>
#include "simple_types.hpp"
#include "subscribable_resource.hpp"
#include "device_category_type.hpp"
#include "list_link.hpp"
#include "lfdi_type.hpp"
#include "sfdi_type.hpp"

namespace sep
{
    // The EndDevice providing the resources available within the DeviceCapabilities.
    struct AbstractDevice : SubscribableResource
    {
        Link configuration_link;
        ListLink der_list_link;
        DeviceCategoryType device_category;
        Link device_information_link;
        Link device_status_link;
        Link file_status_link;
        ListLink ip_interface_list_link;
        LFDIType lfdi;
        ListLink load_shed_availability_list_link;
        ListLink log_event_list_link;
        Link power_status_link;
        SFDIType sfdi; 
    };
        
} // namespace sep

#endif // __ABSTRACT_DEVICE_H__