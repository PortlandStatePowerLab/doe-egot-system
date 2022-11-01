#ifndef __TRUST_CTA2045_DEVICE_H__
#define __TRUST_CTA2045_DEVICE_H__

#include <string>
#include <cea2045/device/DeviceFactory.h>
#include <cea2045/communicationport/CEA2045SerialPort.h>
#include "trust_ucm.hpp"

namespace trust
{
    class cta2045Device
    {
    public:
        // rule of 5
        cta2045Device(cta2045Device &other) = delete;             // clonable
        void operator = (const cta2045Device &) = delete;  // assignable
        static cta2045Device& getInstance(const std::string& context = "");

        cta2045::DeviceInfo getDeviceInfo();
        cta2045::commodity_map getCommodity();
        cea2045::ResponseCodes loadUp(const uint8_t duration);
        cea2045::ResponseCodes shed(const uint8_t duration);
        cea2045::ResponseCodes endShed(const uint8_t duration);
        cea2045::ResponseCodes criticalPeakEvent(const uint8_t duration);
        cea2045::ResponseCodes gridEmergency(const uint8_t duration);

    protected:
        cta2045Device(const std::string& context);
        ~cta2045Device();

    private:
        cea2045::ResponseCodes response_codes_;
        cea2045::CEA2045SerialPort* serial_port_;
        cea2045::ICEA2045DeviceUCM* device_;
        trust::cea2045UCM ucm_;
    };
    
} // namespace trust

#endif // __TRUST_CTA2045_DEVICE_H__