#ifndef __MODBUS_TCP_H__
#define __MODBUS_TCP_H__
#include <string>
#include <cstdint>
#include <modbus/modbus-tcp.h>

class AbstractModbusTCP
{
public:
    virtual ~AbstractModbusTCP () = default;
    virtual void ReadRegisters(const uint16_t offset, const uint16_t length, uint16_t* reg_ptr) = 0;
    virtual void WriteRegisters (const uint16_t offset, const uint16_t length, const uint16_t* reg_ptr);
};

class ModbusTCP : public AbstractModbusTCP
{
public:
    ModbusTCP(const char* ip_address, const uint16_t port);
    ~ModbusTCP();
    void ReadRegisters (const uint16_t offset, const uint16_t length, uint16_t* reg_ptr);
    void WriteRegisters (const uint16_t offset, const uint16_t length, const uint16_t* reg_ptr);

private:
    void Flush ();

private:
    modbus_t* context_ptr_;
}; 

#endif // __MODBUS_TCP_H__