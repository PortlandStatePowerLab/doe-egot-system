#include "include/cta2045/device.hpp"

using namespace cea2045;

namespace cta2045
{
    Device::Device(std::string &context) : serial_port_(context)
    {
        std::cout << "CTA2045 UCM: Connecting to serial port\n";
        if (!serial_port_.open())
        {
            std::cout << "CTA2045 UCM: failed to open serial port\n";
            abort();
        }
        
        

        ICEA2045DeviceUCM *device_ = DeviceFactory::createUCM(&serial_port_, &ucm_);

        device_->start();

        ResponseCodes response = device_->querySuportDataLinkMessages().get();
        if (response.responesCode != ResponseCode::OK)
        {
            std::cout
                << "CTA2045 Device: does not support data link messages with code = "
                << static_cast<int>(response.responesCode);
            abort();
        }

        response = device_->querySuportIntermediateMessages().get();
        if (response.responesCode != ResponseCode::OK)
        {
            std::cout
                << "CTA2045 Device: does not support intermediate messages with code = "
                << static_cast<int>(response.responesCode);
            abort();
        }
    }

    Device::~Device()
    {
    }

    cea2045DeviceInfoResponse Device::getDeviceInfo()
    {
        ResponseCodes response = device_->intermediateGetDeviceInformation().get();
        if (response.responesCode != ResponseCode::OK)
        {
            std::cout 
                << "CTA2045 Device: does not support device info messages with code = " 
                << static_cast<int>(response.responesCode);
            abort();
        }

        return ucm_.device_info_;
    }

    std::unordered_map<Commodity, cea2045CommodityData> Device::getCommodity()
    {
        ResponseCodes response = device_->intermediateGetCommodity().get();
        if (response.responesCode != ResponseCode::OK)
        {
            std::cout 
                << "CTA2045 Device: does not support get commodity with code = " 
                << static_cast<int>(response.responesCode);
            abort();
        }

        return ucm_.commodities_;
    }

} // namespace cta2045