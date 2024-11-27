#ifndef __CTA2045_RECEIVER_H__
#define __CTA2045_RECEIVER_H__
#include <cea2045/communicationport/CEA2045SerialPort.h>
#include <cea2045/device/DeviceFactory.h>
#include <cea2045/processmessage/IUCM.h>
#include <cea2045/util/MSTimer.h>

// This is a receiver class for interacting with a simulated DER
class CTA2045Receiver : public BaseReceiver {
public:
  CTA2045Receiver(CombinedHttpsClient *c);
  ~CTA2045Receiver();
  std::string Import();
  std::string Export();
  std::string GetEnergy();
  std::string GetNameplate();
  std::string Idle();
  std::string CriticalPeakEvent();
  std::string GridEmergencyEvent();

private:
  std::string response_;
  cea2045::CEA2045SerialPort serial_port_;
  cea2045::ResponseCodes responseCodes_;
  cea2045::MSTimer timer_;
  bool shutdown_;
  cea2045::ICEA2045DeviceUCM *device_;
};

#endif //__ECS_DCM_H__
