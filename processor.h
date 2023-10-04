#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <cstdint>

class Processor
{
public:
    Processor();

    uint16_t getIP();
    void setIP(uint16_t address);
    int32_t getRegister(uint32_t number);
    void setRegister(int number, int32_t value);


private:
    int32_t registers[16];
    uint32_t PSW;
};

#endif // PROCESSOR_H
