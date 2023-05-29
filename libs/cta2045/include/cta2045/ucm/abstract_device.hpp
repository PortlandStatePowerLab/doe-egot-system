#ifndef __CTA2045_ABSTRACT_DEVICE_H__
#define __CTA2045_ABSTRACT_DEVICE_H__

#include <cea2045/device/DeviceFactory.h>
#include <cea2045/communicationport/CEA2045SerialPort.h>
#include "ucm.hpp"

namespace cta2045
{
class AbstractDevice
{
public:
    virtual DeviceInfo getDeviceInfo() = 0;
    virtual commodity_map getCommodity() = 0;
    virtual cea2045::ResponseCodes loadUp(const uint8_t duration = 0) = 0;
    virtual cea2045::ResponseCodes shed(const uint8_t duration = 0) = 0;
    virtual cea2045::ResponseCodes endShed(const uint8_t duration = 0) = 0;
    virtual cea2045::ResponseCodes criticalPeakEvent(const uint8_t duration = 0) = 0;
    virtual cea2045::ResponseCodes gridEmergency(const uint8_t duration = 0) = 0;
};
};

#endif // __CTA2045_ABSTRACT_DEVICE_H__