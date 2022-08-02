#include <iostream>
#include <cta2045/device.hpp>

int main(int argc, char const *argv[])
{
  std::cout << "*** DISTRIBUTED CONTROL MODULE ***\n";
  if (argc < 2)
  {
    std::cout << "Please provide serial port path...\n\t Example: ./dcm /dev/ttyUSB0" << std::endl;
    abort();
  }

  std::string serial_port = argv[1];
  
  cta2045::Device device(serial_port);
  
  return 0;
}
