#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <cstdint>
#include "memory.h"

class Command;

class Processor
{
public:    
    Processor();

    uint16_t getIP();
    void setIP(uint16_t address);

    void setCF(uint8_t value);
    void setZF(uint8_t value);
    uint8_t getZF();
    uint8_t getCF();

    Memory &getMemory();
    void run();

    uint32_t registers[16] = {0};

private:
    uint32_t PSW;
    Memory memory;
};

#endif // PROCESSOR_H
