#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

#include "memory.h"
#include "processor.h"

class VirtualMachine
{
public:

    VirtualMachine();
    Memory* getMemory();


private:
    Memory* memory;
    Processor* processor;

};

#endif // VIRTUALMACHINE_H
