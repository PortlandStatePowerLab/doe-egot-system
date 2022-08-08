#include <iostream>
#include <cta2045/device.hpp>
#include <thread>
#include <chrono>
#include <utilities/utilities.hpp>

using namespace cea2045;

int main(int argc, char const *argv[])
{
  std::cout << "*** DISTRIBUTED CONTROL MODULE ***\n";
  if (argc < 2)
  {
    std::cout << "Please provide serial port path...\n\t Example: ./dcm /dev/ttyUSB0" << std::endl;
    abort();
  }

  std::string serial_port = argv[1];

  // cea2045::CEA2045SerialPort serial_port_(serial_port);
  // if (!serial_port_.open())
  // {
  //     std::cout << "CTA2045 UCM: failed to open serial port\n";
  //     abort();
  // }
  
  // UCM ucm = UCM();
  // cea2045::ICEA2045DeviceUCM* device_ = cea2045::DeviceFactory::createUCM(&serial_port_, &ucm);

  // device_->start();

  // cea2045::ResponseCodes response_codes_ = device_->querySuportDataLinkMessages().get();
  // if (response_codes_.responesCode != ResponseCode::OK)
  // {
  //     std::cout
  //         << "CTA2045 Device: does not support data link messages with code = "
  //         << static_cast<int>(response_codes_.responesCode);
  //     abort();
  // }

  // response_codes_ = device_->querySuportIntermediateMessages().get();
  // if (response_codes_.responesCode != ResponseCode::OK)
  // {
  //     std::cout
  //         << "CTA2045 Device: does not support intermediate messages with code = "
  //         << static_cast<int>(response_codes_.responesCode);
  //     abort();
  // }

  // response_codes_ = device_->intermediateGetCommodity().get();
  // if (response_codes_.responesCode != ResponseCode::OK)
  // {
  //     std::cout
  //         << "CTA2045 Device: does not support getCommodity with code = "
  //         << static_cast<int>(response_codes_.responesCode);
  //     abort();
  // }

  // device_->shutDown();
  // delete device_;

  int energy_take = 1;
  while (energy_take > 0){
    cta2045::Device* device = cta2045::Device::getInstance(serial_port);
    cta2045::commodity_map commodities = device->getCommodity();
    cea2045::cea2045CommodityData data = commodities.at(psu::utilities::ToUnderlyingType(cta2045::Commodity::kPresentEnergy));
    energy_take = data.getCumulativeAmount();
    device->loadUp();
    std::this_thread::sleep_for(std::chrono::seconds(10));
  }

  return 0;
}


