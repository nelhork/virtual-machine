#include "processor.h"

Processor::Processor()
{

}

uint16_t Processor::getIP() {
    return PSW >> 16;
}

void Processor::setIP(uint16_t address) {
    int32_t newaddr = address << 16;
    PSW &= 0xffff;
    PSW += newaddr;
}

int32_t Processor::getRegister(int number) {
    return registers[number];
}

void Processor::setRegister(int number, int32_t value) {
    registers[number] = value;
}
