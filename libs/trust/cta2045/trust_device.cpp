#include <https/client/client.hpp>
#include <trust/cta2045/trust_device.hpp>
#include <trust/xml/utils.hpp>
#include <utilities/utilities.hpp>

using namespace cea2045;
static bool initialized_s;

namespace trust {

cta2045Device::cta2045Device(const std::string &ctx, const https::Context &dtm)
    : dtm_client(dtm), ucm_(dtm) {
  serial_port_ = new CEA2045SerialPort(ctx);
  if (!serial_port_->open()) {
    std::cout << "CTA2045 UCM: failed to open serial port\n";
    abort();
  }

  device_ = DeviceFactory::createUCM(serial_port_, &ucm_);

  device_->start();

  response_codes_ = device_->querySuportDataLinkMessages().get();
  if (response_codes_.responesCode != ResponseCode::OK) {
    std::cout
        << "CTA2045 Device: does not support data link messages with code = "
        << static_cast<int>(response_codes_.responesCode);
    abort();
  }

  response_codes_ = device_->querySuportIntermediateMessages().get();
  if (response_codes_.responesCode != ResponseCode::OK) {
    std::cout
        << "CTA2045 Device: does not support intermediate messages with code = "
        << static_cast<int>(response_codes_.responesCode);
    abort();
  }
}

cta2045Device::~cta2045Device() {
  device_->shutDown();
  delete device_;
  delete serial_port_;
}

cta2045Device &cta2045Device::getInstance(const std::string &ctx,
                                          const https::Context &dtm) {
  if (ctx != "/na" && !initialized_s) {
    initialized_s = true;
  }

  if (initialized_s) {
    static cta2045Device instance(ctx, dtm);
    return instance;
  }

  throw "Trust client must be initialized with GSP and DTMC context first!";
}

cta2045::DeviceInfo cta2045Device::getDeviceInfo() {
  trust::Message msg;
  msg.to = "DER";
  msg.from = "DCM";
  msg.timestamp = psu::utilities::getTime();
  msg.contents["request"] = "intermediateGetDeviceInformation";
  dtm_client.Post("/na", trust::Stringify(msg));

  response_codes_ = device_->intermediateGetDeviceInformation().get();

  if (response_codes_.responesCode != ResponseCode::OK) {
    std::cout
        << "CTA2045 Device: does not support device info messages with code = "
        << static_cast<int>(response_codes_.responesCode);
    abort();
  }

  return ucm_.device_info_;
}

cta2045::commodity_map cta2045Device::getCommodity() {
  trust::Message msg;
  msg.to = "DER";
  msg.from = "DCM";
  msg.timestamp = psu::utilities::getTime();
  msg.contents["request"] = "intermediateGetCommodity";
  dtm_client.Post("/na", trust::Stringify(msg));

  response_codes_ = device_->intermediateGetCommodity().get();
  if (response_codes_.responesCode != ResponseCode::OK) {
    std::cout << "CTA2045 Device: does not support get commodity with code = "
              << static_cast<int>(response_codes_.responesCode);
    abort();
  }
  return ucm_.commodities_;
}

cea2045::ResponseCodes cta2045Device::getOperationalState(){
  trust::Message msg;
  msg.to = "DER";
  msg.from = "DCM";
  msg.timestamp = psu::utilities::getTime();
  msg.contents["request"] = "basicQueryOperationalState";
  dtm_client.Post("/na", trust::Stringify(msg));

  response_codes_ = device_->basicQueryOperationalState().get();
  if (response_codes_.responesCode != ResponseCode::OK) {
    std::cout << "CTA2045 Device: does not support QueryOperationalState with code = "
              << static_cast<int>(response_codes_.responesCode);
    abort();
  }
  return response_codes_;
}

cea2045::ResponseCodes cta2045Device::getOutsideCommunicationStatus(cea2045::OutsideCommuncatonStatusCode code){
  trust::Message msg;
  msg.to = "DER";
  msg.from = "DCM";
  msg.timestamp = psu::utilities::getTime();
  msg.contents["request"] = "basicOutsideCommConnectionStatus";
  msg.contents["code"] = std::to_string((int)code);
  dtm_client.Post("/na", trust::Stringify(msg));

  response_codes_ = device_->basicOutsideCommConnectionStatus(code).get();
  if (response_codes_.responesCode != ResponseCode::OK) {
    std::cout << "CTA2045 Device: does not support basicOutsideCommConnectionStatus with code = "
              << static_cast<int>(response_codes_.responesCode);
    abort();
  }
  return response_codes_;
}

cea2045::ResponseCodes cta2045Device::loadUp(const uint8_t duration) {
  trust::Message msg;
  msg.to = "DER";
  msg.from = "DCM";
  msg.timestamp = psu::utilities::getTime();
  msg.contents["request"] = "basicLoadUp";
  msg.contents["duration"] = std::to_string(duration);
  dtm_client.Post("/na", trust::Stringify(msg));

  response_codes_ = device_->basicLoadUp(duration).get();
  if (response_codes_.responesCode != ResponseCode::OK) {
    std::cout << "CTA2045 Device: does not support loadUp with code = "
              << static_cast<int>(response_codes_.responesCode);
    abort();
  }
  return response_codes_;
}

cea2045::ResponseCodes cta2045Device::shed(const uint8_t duration) {
  trust::Message msg;
  msg.to = "DER";
  msg.from = "DCM";
  msg.timestamp = psu::utilities::getTime();
  msg.contents["request"] = "basicLoadUp";
  msg.contents["duration"] = std::to_string(duration);
  dtm_client.Post("/na", trust::Stringify(msg));

  response_codes_ = device_->basicShed(duration).get();
  if (response_codes_.responesCode != ResponseCode::OK) {
    std::cout << "CTA2045 Device: does not support shed with code = "
              << static_cast<int>(response_codes_.responesCode);
    abort();
  }
  return response_codes_;
}

cea2045::ResponseCodes cta2045Device::endShed(const uint8_t duration) {
  trust::Message msg;
  msg.to = "DER";
  msg.from = "DCM";
  msg.timestamp = psu::utilities::getTime();
  msg.contents["request"] = "basicEndShed";
  msg.contents["duration"] = std::to_string(duration);
  dtm_client.Post("/na", trust::Stringify(msg));

  response_codes_ = device_->basicEndShed(duration).get();
  if (response_codes_.responesCode != ResponseCode::OK) {
    std::cout << "CTA2045 Device: does not support endShed with code = "
              << static_cast<int>(response_codes_.responesCode);
    abort();
  }
  return response_codes_;
}

cea2045::ResponseCodes
cta2045Device::criticalPeakEvent(const uint8_t duration) {
  trust::Message msg;
  msg.to = "DER";
  msg.from = "DCM";
  msg.timestamp = psu::utilities::getTime();
  msg.contents["request"] = "basicCriticalPeakEvent";
  msg.contents["duration"] = std::to_string(duration);
  dtm_client.Post("/na", trust::Stringify(msg));

  response_codes_ = device_->basicCriticalPeakEvent(duration).get();
  if (response_codes_.responesCode != ResponseCode::OK) {
    std::cout
        << "CTA2045 Device: does not support criticalPeakEvent with code = "
        << static_cast<int>(response_codes_.responesCode);
    abort();
  }
  return response_codes_;
}

cea2045::ResponseCodes cta2045Device::gridEmergency(const uint8_t duration) {
  trust::Message msg;
  msg.to = "DER";
  msg.from = "DCM";
  msg.timestamp = psu::utilities::getTime();
  msg.contents["request"] = "basicGridEmergency";
  msg.contents["duration"] = std::to_string(duration);
  dtm_client.Post("/na", trust::Stringify(msg));

  response_codes_ = device_->basicGridEmergency(duration).get();
  if (response_codes_.responesCode != ResponseCode::OK) {
    std::cout << "CTA2045 Device: does not support gridEmergency with code = "
              << static_cast<int>(response_codes_.responesCode);
    abort();
  }
  return response_codes_;
}

} // namespace trust
