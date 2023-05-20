#ifndef __DEVICE_CAPABILITY_H__
#define __DEVICE_CAPABILITY_H__
#include "simple_types.hpp"
#include "function_set_assignments_base.hpp"
#include "end_device.hpp"
#include "mirror_usage_point.hpp"
#include "self_device.hpp"

namespace sep
{
    struct DeviceCapabilityLink : Link {};
    
    // Returned by the URI provided by DNS-SD, to allow clients to find the URIs 
    // to the resources in which they are interested.
    struct DeviceCapability : FunctionSetAssignmentsBase
    {
        // Optional
        UInt32 poll_rate = 900;
        EndDeviceListLink end_device_list_link;
        MirrorUsagePointListLink mirror_usage_point_list_link;
        SelfDeviceLink self_device_link;
    };
} // namespace sep

#endif // __DEVICE_CAPABILITY_H__