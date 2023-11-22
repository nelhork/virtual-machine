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

void VirtualMachine::load(std::string filename) { // загрузка значений из файла в память
    int memoryAddress = 0; // индекс массива памяти

    std::fstream instructionFile;
    instructionFile.open(filename);

    std::string str;
    while (instructionFile >> str) {
        memory->set(memoryAddress, static_cast<uint8_t>(stoi(str, nullptr, 16))); // перевод из строки в шестнадцатеричное число
        memoryAddress++;
    }
    instructionFile.close();

    processor->setIP(0);
}

void VirtualMachine::run() { // запуск программы на выполнение
    uint8_t opcode = 0, byte2, byte3; // структура команды 3 байта

    int ip = processor->getIP();

    while ((opcode = memory->get(ip++)) != 0x54) {
        byte2 = memory->get(ip++);
        byte3 = memory->get(ip++);

        processor->setIP(ip);

        try {
            Command* command = Command::getCommand(opcode, byte2, byte3); // получение команды
            // полиморфизм, getCommand вернет один из классов-наследников
            (*command)(this); // вызов функтора, нужен для определения команды

            ip = processor->getIP();
        } catch (const char* error) {
            std::cout << "exception: " << error << std::endl;
            break;
        }
    }
}

// циклические зависимости
