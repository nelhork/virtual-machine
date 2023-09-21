#ifndef MEMORY_H
#define MEMORY_H

#include <cstdint>


class Memory
{
public:
    Memory();
    int8_t get(int16_t address);
    void set(int16_t address, int8_t value);

private:
    int8_t* mem;
};

#endif // MEMORY_H
