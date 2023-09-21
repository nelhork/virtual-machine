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

void VirtualMachine::load(std::string filename) {
    int count = 0;
    std::fstream file;
    file.open(filename);
    std::string str;
    while (file >> str) {
        memory->set(count, stoi(str, nullptr,16)); // перевод из строки в шестнадцатеричное число
        count++;
    }
    memory->set(count, 0x54);
    count++;

    memory->set(count, 0);
    count++;

    memory->set(count, 0);
    file.close();

    processor->setIP(0);
}

void VirtualMachine::run() {
    int8_t opcode = 0, byte2, byte3;
    int ip = processor->getIP();
    while (opcode != 0x54) {
        opcode = memory->get(ip++);
        byte2 = memory->get(ip++);
        byte3 = memory->get(ip++);
        Command* command = Command::getCommand(opcode, byte2, byte3);
        (*command)(this);
    }
}


