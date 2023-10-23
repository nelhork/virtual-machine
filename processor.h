#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <cstdint>

class Processor
{
public:
    Processor();

    uint16_t getIP();
    void setIP(uint16_t address);
    int32_t getRegisterVal(uint8_t number);
    void setRegisterVal(uint8_t number, int32_t value);
    void setCF(uint8_t value);
    void setZF(uint8_t value);
    uint8_t getZF();
    uint8_t getCF();

private:
    uint32_t registers[16];
    uint32_t PSW;
};

#endif // PROCESSOR_H
