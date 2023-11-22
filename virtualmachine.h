#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

#include "memory.h"
#include "processor.h"
#include <fstream>
#include <string>

class Command;

class VirtualMachine
{
public:
    VirtualMachine();

    Memory* getMemory();
    Processor* getProcessor();

    void load(std::string filename);
    void run();

private:
    Memory* memory;
    Processor* processor;
};

#endif // VIRTUALMACHINE_H
