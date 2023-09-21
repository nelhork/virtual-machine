#include "memory.h"

Memory::Memory()
{
    mem = new int8_t[65536];
}

int8_t Memory::get(int16_t address)
{
    return mem[address];
}

void Memory::set(int16_t address, int8_t value)
{
    mem[address] = value;
}
