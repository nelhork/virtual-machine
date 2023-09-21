#include "command.h"

Command::Command(int8_t byte1, int8_t byte2, int8_t byte3)
{
    this->byte1 = byte1;
    this->byte2 = byte2;
    this->byte3 = byte3;
}

void In::operator()(VirtualMachine *vm)
{
    int32_t value;
    auto registerNumber = byte2 & 0x0f;
    std::cout << "Program is asking for input: " << std::endl;
    std::cin >> value;
    vm->getProcessor()->setRegister(registerNumber, value);
}

void Out::operator()(VirtualMachine *vm)
{
    auto regNum = byte2 & 0x0f;
    std::cout << "Program output:\n" << vm->getProcessor()->getRegister(regNum) << std::endl;
}

void Add::operator()(VirtualMachine *vm)
{
    auto value1 = vm->getProcessor()->getRegister(byte2 & 0x0f); // обнуление старшей половины байта для получения номера первого регистра
    auto value2 = vm->getMemory()->get(vm->getProcessor()->getRegister(byte2 >> 4)); // сдвиг вправо на 4 бита для получения номера второго регистра
    vm->getProcessor()->setRegister(1, value1 + value2);
}

void MovRM::operator()(VirtualMachine *vm)
{
    int16_t address = vm->getProcessor()->getRegister((byte2 >> 4) & 0x0f);
    int8_t val = vm->getProcessor()->getRegister(byte2 & 0x0f);
    vm->getMemory()->set(address, val);
}

void Lea::operator()(VirtualMachine *vm)
{
    auto address = ((byte2 << 2) & 0xf0) + byte3;
    vm->getProcessor()->setRegister(15, address);
}
