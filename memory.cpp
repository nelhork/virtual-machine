#include "memory.h"
#include <iostream>

Memory::Memory()
{
    mem = new int8_t[65536];
}

int8_t Memory::get(int16_t address)
{
    std::cout << "mem read: " << static_cast<int>(mem[address]) << " at " << address << std::endl;
    return mem[address];
}

void Memory::set(int16_t address, int8_t value)
{
    std::cout << "mem write: " << static_cast<int>(value) << " at " << address << std::endl;
    mem[address] = value;
}
