#include "processor.h"
#include <iostream>

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

int32_t Processor::getRegister(uint32_t number) {
    std::cout << "register read: " << registers[number] << " at " << number << std::endl;
    return registers[number];
}

void Processor::setRegister(int number, int32_t value) {
    std::cout << "register write: " << static_cast<int>(value) << " at " << number << std::endl;
    registers[number] = value;
}
