#ifndef __CTA2045_DEVICE_H__
#define __CTA2045_DEVICE_H__

#include "ucm.hpp"
#include <cea2045/communicationport/CEA2045SerialPort.h>
#include <cea2045/device/DeviceFactory.h>
#include <mutex>
#include <string>

// Singleton Design Pattern
namespace cta2045 {
class Device {
public:
  // rule of 5
  Device(Device &other) = delete;          // clonable
  void operator=(const Device &) = delete; // assignable
  static Device *getInstance(const std::string &context);

  DeviceInfo getDeviceInfo();
  commodity_map getCommodity();
  cea2045::ResponseCodes loadUp(const uint8_t duration = 0);
  cea2045::ResponseCodes shed(const uint8_t duration = 0);
  cea2045::ResponseCodes endShed(const uint8_t duration = 0);
  cea2045::ResponseCodes criticalPeakEvent(const uint8_t duration = 0);
  cea2045::ResponseCodes gridEmergency(const uint8_t duration = 0);

protected:
  Device(const std::string &context);
  ~Device() noexcept;

private:
  cea2045::ResponseCodes response_codes_;
  cea2045::CEA2045SerialPort *serial_port_;
  UCM *ucm_;
  cea2045::ICEA2045DeviceUCM *device_;

private:
  // thread-safe singleton instance
  static Device *instance_;
  static std::mutex mutex_;
};

} // namespace cta2045

#endif // __CTA2045_DEVICE_H__
