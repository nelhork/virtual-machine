#include "processor.h"
#include <iostream>
#include <bitset>

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

int32_t Processor::getRegisterVal(uint8_t number) {
    //std::cout << "register read: " << registers[number] << " at " << number << std::endl;
    return registers[number];
}

void Processor::setRegisterVal(uint8_t number, int32_t value) {
    //std::cout << "register write: " << static_cast<int>(value) << " at " << number << std::endl;
    registers[number] = value;
}

void Processor::setCF(uint8_t value)
{
    std::bitset<32> bitsetPSW(PSW);
    bitsetPSW[1] = value;
    PSW = bitsetPSW.to_ulong();
    std::cout << "setting CF to " << (int)value << "\n";
}

void Processor::setZF(uint8_t value)
{
    std::bitset<32> bitsetPSW(PSW);
    bitsetPSW[0] = value;
    PSW = bitsetPSW.to_ulong();
    std::cout << "setting ZF to " << (int)value << "\n";
}

uint8_t Processor::getZF()
{
    std::bitset<32> bitsetPSW(PSW);
    return bitsetPSW[0];
}

uint8_t Processor::getCF()
{
    std::bitset<32> bitsetPSW(PSW);
    return bitsetPSW[1];
}
