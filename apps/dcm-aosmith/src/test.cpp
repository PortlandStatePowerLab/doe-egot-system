
#include <chrono>
#include <https/client/client.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <trust/cta2045/trust_device.hpp>
#include <utilities/utilities.hpp>

std::string g_program_path;

int main(int argc, char **argv) {
  std::cout << "Starting DCM for AOSmith water heater\n";
  g_program_path = psu::utilities::getProgramPath(argv);

  https::Context dtm_ctx = {"1", g_program_path, "0.0.0.0", "8090"};
  trust::cta2045Device::getInstance("/dev/ttyAMA0", dtm_ctx);
  std::this_thread::sleep_for(std::chrono::seconds(1));
  trust::cta2045Device::getInstance("/dev/ttyAMA0", dtm_ctx).getOutsideCommunicationStatus(cea2045::OutsideCommuncatonStatusCode::Found);
  trust::cta2045Device::getInstance("/dev/ttyAMA0", dtm_ctx).getOperationalState();
  trust::cta2045Device::getInstance("/dev/ttyAMA0", dtm_ctx).getDeviceInfo();
  trust::cta2045Device::getInstance("/dev/ttyAMA0", dtm_ctx).getCommodity();
  trust::cta2045Device::getInstance("/dev/ttyAMA0", dtm_ctx).loadUp(0); 
  std::this_thread::sleep_for(std::chrono::seconds(10));
  trust::cta2045Device::getInstance("/dev/ttyAMA0", dtm_ctx).getOperationalState();
  trust::cta2045Device::getInstance("/dev/ttyAMA0", dtm_ctx).getCommodity();
  std::this_thread::sleep_for(std::chrono::seconds(10));
  trust::cta2045Device::getInstance("/dev/ttyAMA0", dtm_ctx).endShed(0);
  trust::cta2045Device::getInstance("/dev/ttyAMA0", dtm_ctx).criticalPeakEvent(60);
  std::this_thread::sleep_for(std::chrono::seconds(10));
  trust::cta2045Device::getInstance("/dev/ttyAMA0", dtm_ctx).getOperationalState();
  trust::cta2045Device::getInstance("/dev/ttyAMA0", dtm_ctx).endShed(0);
  trust::cta2045Device::getInstance("/dev/ttyAMA0", dtm_ctx).gridEmergency(60);
  std::this_thread::sleep_for(std::chrono::seconds(10));
  trust::cta2045Device::getInstance("/dev/ttyAMA0", dtm_ctx).getOperationalState();
  trust::cta2045Device::getInstance("/dev/ttyAMA0", dtm_ctx).endShed(0);
  trust::cta2045Device::getInstance("/dev/ttyAMA0", dtm_ctx).shed(60);
  std::this_thread::sleep_for(std::chrono::seconds(10));
  trust::cta2045Device::getInstance("/dev/ttyAMA0", dtm_ctx).getOperationalState();
  trust::cta2045Device::getInstance("/dev/ttyAMA0", dtm_ctx).loadUp(0); 
  std::this_thread::sleep_for(std::chrono::seconds(10));
  trust::cta2045Device::getInstance("/dev/ttyAMA0", dtm_ctx).getOperationalState();
  trust::cta2045Device::getInstance("/dev/ttyAMA0", dtm_ctx).getCommodity();
  trust::cta2045Device::getInstance("/dev/ttyAMA0", dtm_ctx).shed(0);
return 0;
}
