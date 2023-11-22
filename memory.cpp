#include <iostream>
#include "memory.h"

Memory::Memory()
{
    mem = new uint8_t[65536];
}

uint8_t Memory::get(uint16_t address)
{
    return mem[address];
}

uint32_t Memory::get32(uint16_t address)
{
    ByteAccess data;
    for (int i = 0; i < 4; ++i) {
        data.byteValue[i] = mem[address + i];
    }

    return data.intValue;
}

void Memory::set(uint16_t address, uint8_t value)
{
    mem[address] = value;
}

void Memory::set(uint16_t address, uint32_t value)
{
    ByteAccess data;
    data.intValue = value;

    for (int i = 0; i < 4; i++) {
        mem[address + i] = data.byteValue[i];
    }
}

Memory::~Memory()
{
    delete[] mem;
}
