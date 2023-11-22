#include <iostream>
#include <bitset>
#include "processor.h"
#include "command.h"

Processor::Processor()
{
    PSW = 0;
}

uint16_t Processor::getIP() {
    return PSW >> 16;
}

void Processor::setIP(uint16_t address) {
    int32_t newaddr = address << 16;
    PSW &= 0xffff;
    PSW += newaddr;
}

void Processor::setCF(uint8_t value)
{
    std::bitset<32> bitsetPSW(PSW);
    bitsetPSW[1] = value;
    PSW = bitsetPSW.to_ulong();
}

void Processor::setZF(uint8_t value)
{
    std::bitset<32> bitsetPSW(PSW);
    bitsetPSW[0] = value;
    PSW = bitsetPSW.to_ulong();
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

Memory &Processor::getMemory()
{
    return memory;
}

void Processor::run()
{
    uint8_t opcode = 0, byte2, byte3; // структура команды 3 байта

    int ip = getIP();

    while ((opcode = memory.get(ip++)) != 0x54) {
        byte2 = memory.get(ip++);
        byte3 = memory.get(ip++);

        setIP(ip);

        try {
            Command* command = Command::getCommand(opcode, byte2, byte3); // получение команды
            // полиморфизм, getCommand вернет один из классов-наследников
            (*command)(this); // вызов функтора, нужен для определения команды

            ip = getIP();
        } catch (const char* error) {
            std::cout << "exception: " << error << std::endl;
            break;
        }
    }
}
