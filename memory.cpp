#include "memory.h"
#include <iostream>

Memory::Memory()
{
    mem = new uint8_t[65536];
}

uint8_t Memory::get(uint16_t address)
{
    //std::cout << "mem read: " << static_cast<int>(mem[address]) << " at " << address << std::endl;
    return mem[address];
}

uint32_t Memory::get32(uint16_t address)
{
    uint32_t value = 0;
    value = value | static_cast<uint32_t>(mem[address]);
    value = value | static_cast<uint32_t>(mem[address + 1]) << 8;
    value = value | static_cast<uint32_t>(mem[address + 2]) << 16;
    value = value | static_cast<uint32_t>(mem[address + 3]) << 24;
    return value;
}

void Memory::set(uint16_t address, uint8_t value)
{
    //std::cout << "mem write: " << static_cast<int>(value) << " at " << address << std::endl;
    mem[address] = value;
}

void Memory::set(uint16_t address, uint32_t value)
{
    int8_t bytes[4];
    bytes[0] = static_cast<uint8_t>(value & 0xff);
    bytes[1] = static_cast<uint8_t>((value >> 8) & 0xff);
    bytes[2] = static_cast<uint8_t>((value >> 16) & 0xff);
    bytes[3] = static_cast<uint8_t>((value >> 24) & 0xff);

    for (int i = 0; i < 4; i++) {
        mem[address + i] = bytes[i];
    }
}
