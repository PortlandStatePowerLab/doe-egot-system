#ifndef __ABSTRACT_DEVICE_H__
#define __ABSTRACT_DEVICE_H__
#include "simple_types.hpp"
#include "subscribable_resource.hpp"
#include "device_category_type.hpp"
#include "configuration.hpp"
#include "der.hpp"
#include "device_information.hpp"
#include "device_status.hpp"
#include "file_status.hpp"
#include "ip_interface.hpp"
#include "load_shed_availability.hpp"
#include "log_event.hpp"
#include "power_status.hpp"

namespace sep
{
    // The EndDevice providing the resources available within the DeviceCapabilities.
    struct AbstractDevice : SubscribableResource
    {
        SFDIType sfdi; 

        // Optionals
        ConfigurationLink configuration_link;
        DERListLink der_list_link;
        DeviceCategoryType device_category;
        DeviceInformationLink device_information_link;
        DeviceStatusLink device_status_link;
        FileStatusLink file_status_link;
        IPInterfaceListLink ip_interface_list_link;
        HexBinary160 lfdi;
        LoadShedAvailabilityListLink load_shed_availability_list_link;
        LogEventListLink log_event_list_link;
        PowerStatusLink power_status_link;
    };
        
} // namespace sep

#endif // __ABSTRACT_DEVICE_H__