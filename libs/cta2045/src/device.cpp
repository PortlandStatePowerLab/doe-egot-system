#include "include/cta2045/device.hpp"

using namespace cea2045;

cta2045::Device* cta2045::Device::instance_{nullptr};
std::mutex cta2045::Device::mutex_;

namespace cta2045
{
    Device::Device(const std::string &context)
    {
        serial_port_ = new CEA2045SerialPort(context);
        if (!serial_port_->open())
        {
            std::cout << "CTA2045 UCM: failed to open serial port\n";
            abort();
        }
        
        ucm_ = new UCM();
        device_ = DeviceFactory::createUCM(serial_port_, ucm_);

        device_->start();

        response_codes_ = device_->querySuportDataLinkMessages().get();
        if (response_codes_.responesCode != ResponseCode::OK)
        {
            std::cout
                << "CTA2045 Device: does not support data link messages with code = "
                << static_cast<int>(response_codes_.responesCode);
            abort();
        }

        response_codes_ = device_->querySuportIntermediateMessages().get();
        if (response_codes_.responesCode != ResponseCode::OK)
        {
            std::cout
                << "CTA2045 Device: does not support intermediate messages with code = "
                << static_cast<int>(response_codes_.responesCode);
            abort();
        }
    }

    Device::~Device()
    {
        device_->shutDown();
        delete device_;
        delete ucm_;
        delete serial_port_;
    }

    Device* Device::getInstance(const std::string& context)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (instance_ == nullptr)
        {
            instance_ = new Device(context);
        }
        return instance_;
    }

    DeviceInfo Device::getDeviceInfo()
    {
        response_codes_ = device_->intermediateGetDeviceInformation().get();
        if (response_codes_.responesCode != ResponseCode::OK)
        {
            std::cout 
                << "CTA2045 Device: does not support device info messages with code = " 
                << static_cast<int>(response_codes_.responesCode);
            abort();
        }
        return ucm_->device_info_;
    }

    commodity_map Device::getCommodity()
    {
        response_codes_ = device_->intermediateGetCommodity().get();
        if (response_codes_.responesCode != ResponseCode::OK)
        {
            std::cout 
                << "CTA2045 Device: does not support get commodity with code = " 
                << static_cast<int>(response_codes_.responesCode);
            abort();
        }
        return ucm_->commodities_;
    }

    cea2045::ResponseCodes Device::loadUp(const uint8_t duration)
    {
        response_codes_ = device_->basicLoadUp(duration).get();
        if (response_codes_.responesCode != ResponseCode::OK)
        {
            std::cout 
                << "CTA2045 Device: does not support loadUp with code = " 
                << static_cast<int>(response_codes_.responesCode);
            abort();
        }
        return response_codes_;
    }
    
    cea2045::ResponseCodes Device::shed(const uint8_t duration)
    {
        response_codes_ = device_->basicShed(duration).get();
        if (response_codes_.responesCode != ResponseCode::OK)
        {
            std::cout 
                << "CTA2045 Device: does not support shed with code = " 
                << static_cast<int>(response_codes_.responesCode);
            abort();
        }
        return response_codes_;
    }
    
    cea2045::ResponseCodes Device::endShed(const uint8_t duration)
    {
        response_codes_ = device_->basicEndShed(duration).get();
        if (response_codes_.responesCode != ResponseCode::OK)
        {
            std::cout 
                << "CTA2045 Device: does not support endShed with code = " 
                << static_cast<int>(response_codes_.responesCode);
            abort();
        }
        return response_codes_;
    }
    
    cea2045::ResponseCodes Device::criticalPeakEvent(const uint8_t duration)
    {
        response_codes_ = device_->basicCriticalPeakEvent(duration).get();
        if (response_codes_.responesCode != ResponseCode::OK)
        {
            std::cout 
                << "CTA2045 Device: does not support criticalPeakEvent with code = " 
                << static_cast<int>(response_codes_.responesCode);
            abort();
        }
        return response_codes_;
    }
    
    cea2045::ResponseCodes Device::gridEmergency(const uint8_t duration)
    {
        response_codes_ = device_->basicGridEmergency(duration).get();
        if (response_codes_.responesCode != ResponseCode::OK)
        {
            std::cout 
                << "CTA2045 Device: does not support gridEmergency with code = " 
                << static_cast<int>(response_codes_.responesCode);
            abort();
        }
        return response_codes_;
    }

} // namespace cta2045