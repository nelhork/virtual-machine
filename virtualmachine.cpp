#include "virtualmachine.h"

VirtualMachine::VirtualMachine()
{
    memory = new Memory;
    processor = new Processor;


}

Memory *VirtualMachine::getMemory()
{
    return memory;
}

Processor *VirtualMachine::getProcessor()
{
    return processor;
}
