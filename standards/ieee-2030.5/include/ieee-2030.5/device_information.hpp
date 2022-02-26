#ifndef __DEVICE_INFORMATION_H__
#define __DEVICE_INFORMATION_H__

#include <cstdint>
#include "resource.hpp"
#include "drlc_capabilities.hpp"
#include "gps_location_type.hpp"

namespace sep
{
    // Bitmap indicating the function sets used by the device as a client.
    enum class FunctionsImplemented : uint64_t
    {
        kDeviceCapability = 0 << 1,
        kSelfDevice = 0 << 2,
        kEndDevice = 0 << 3,
        kFunctionSetAssignments = 0 << 4,
        kSubscriptionNotification = 0 << 5,
        kResponse = 0 << 6,
        kTime = 0 << 7,
        kDeviceInformation = 0 << 8,
        kPowerStatus = 0 << 9,
        kNetworkStatus = 0 << 10,
        kLogEvent = 0 << 11,
        kConfiguration = 0 << 12,
        kSoftwareDownload = 0 << 13,
        kDRLC = 0 << 14,
        kMetering = 0 << 15,
        kPricing = 0 << 16,
        kMessaging = 0 << 17,
        kBilling = 0 << 18,
        kPrepayment = 0 << 19,
        kFlowReservation = 0 << 20,
        kDERControl = 0 << 21
    };
    
    // Contains identification and other information about the device that 
    // changes very infrequently, typically only when updates are applied, 
    // if ever.
    struct DeviceInformation : Resource
    {
        DRLCCapabilities drlc_capabilities;
        FunctionsImplemented function_implementated;
        GPSLocationType gps_location;

    };
} // namespace sep



#endif // __DEVICE_INFORMATION_H__