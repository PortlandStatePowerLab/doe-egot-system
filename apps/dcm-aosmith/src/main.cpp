#include <cta2045/device.hpp>
#include <cta2045/ucm.hpp>
#include <iostream>
#include <string>

std::string g_program_path;

int main(int argc, char **argv) {
  std::cout << "Starting DCM for AOSmith water heater\n";
  cta2045::DeviceInfo info =
      cta2045::Device::getInstance("ttl/0")->getDeviceInfo();
  std::cout << "info : " << info.vendor_id << "\n"
            << info.device_type << "\n"
            << info.firmware_year << std::endl;
  return 0;
}
