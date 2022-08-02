#ifndef __CTA2045_DEVICE_H__
#define __CTA2045_DEVICE_H__

#include <string>
#include <cea2045/device/DeviceFactory.h>
#include <cea2045/communicationport/CEA2045SerialPort.h>
#include "ucm.hpp"

namespace cta2045
{
    class Device
    {
    public:
        Device(std::string& context);
        ~Device();

        cea2045::cea2045DeviceInfoResponse getDeviceInfo();
        std::unordered_map<Commodity, cea2045::cea2045CommodityData> getCommodity();

    private:
        cea2045::CEA2045SerialPort serial_port_;
        UCM ucm_;
        cea2045::ICEA2045DeviceUCM* device_;
    };
    
} // namespace cta2045

#endif // __CTA2045_DEVICE_H__