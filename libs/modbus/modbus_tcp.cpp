#include "include/modbus/modbus_tcp.hpp"
#include <iostream>

ModbusTCP::ModbusTCP(const char *ip_address, const uint16_t port)
{
    std::cout << "Connecting to Modbus device...\n" 
        << "\tIP Address : " << ip_address << '\n'
        << "\tPort :  " << port << std::endl;

    context_ptr_ = modbus_new_tcp(ip_address, port);

    if (modbus_connect(context_ptr_) == -1)
    {
        std::cout << "\t[Modbus Connect Error] : " << modbus_strerror(errno) << std::endl;
    }
}

ModbusTCP::~ModbusTCP()
{
    std::cout << "Closing modbus connection..." << std::endl;

    ModbusTCP::Flush();
    modbus_close(context_ptr_);
    modbus_free(context_ptr_);
}

void ModbusTCP::ReadRegisters(const uint16_t offset, const uint16_t length, uint16_t *reg_ptr)
{
    if (modbus_read_registers(context_ptr_, offset, length, reg_ptr) == -1)
    {
        reg_ptr = nullptr;
        std::cout << "\t[Modbus Read Error] : " << modbus_strerror(errno) << std::endl;
        ModbusTCP::Flush();
    }
}

void ModbusTCP::WriteRegisters(const uint16_t offset, const uint16_t length, const uint16_t *reg_ptr)
{
    if (modbus_write_registers(context_ptr_, offset, length, reg_ptr) == -1)
    {
        reg_ptr = nullptr;
        std::cout << "\t[Modbus Write Error] : " << modbus_strerror(errno) << std::endl;
        ModbusTCP::Flush();
    }
}


void ModbusTCP::Flush() 
{
    if (modbus_flush(context_ptr_) == -1)
    {
        std::cout << "\t[Modbus Flush Error] : " << modbus_strerror(errno) << std::endl;
        ModbusTCP::Flush();
    }
}
