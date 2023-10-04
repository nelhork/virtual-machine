#include "virtualmachine.h"
#include "command.h"

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

    for (int i = 0; i < 20; i++) {
        std::cout << static_cast<uint16_t>(memory->get(i)) << " ";
    }
    file.close();

    processor->setIP(0);
}

void VirtualMachine::run() {
    int8_t opcode = 0, byte2, byte3;
    int ip = processor->getIP();
    while ((opcode = memory->get(ip++)) != 0x54) {
        byte2 = memory->get(ip++);
        byte3 = memory->get(ip++);
        Command* command = Command::getCommand(opcode, byte2, byte3);
        (*command)(this);
    }
}

// циклические зависимости


