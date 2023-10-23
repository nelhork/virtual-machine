#include "command.h"

Command::Command(uint8_t byte1, uint8_t byte2, uint8_t byte3)
{
    this->byte1 = byte1;
    this->byte2 = byte2;
    this->byte3 = byte3;
}

Command *Command::getCommand(uint8_t opcode, uint8_t byte2, uint8_t byte3)
{
    switch(opcode) {
    case Commands::IN:
        return new In(opcode, byte2, byte3);
    case Commands::OUT:
        return new Out(opcode, byte2, byte3);
    case Commands::ADD:
        return new Add(opcode, byte2, byte3);
    case Commands::SUB:
        return new Sub(opcode, byte2, byte3);
    case Commands::MUL:
        return new Mul(opcode, byte2, byte3);
    case Commands::DIV:
        return new Div(opcode, byte2, byte3);
    case Commands::FADD:
        return new Fadd(opcode, byte2, byte3);
    case Commands::FSUB:
        return new Fsub(opcode, byte2, byte3);
    case Commands::FMUL:
        return new Fmul(opcode, byte2, byte3);
    case Commands::FDIV:
        return new Fdiv(opcode, byte2, byte3);
    case Commands::FIN:
        return new Fin(opcode, byte2, byte3);
    case Commands::FOUT:
        return new Fout(opcode, byte2, byte3);
    case Commands::MOVRM:
        return new MovRM(opcode, byte2, byte3);
    case Commands::MOVRR:
        return new MovRR(opcode, byte2, byte3);
    case Commands::MOVMR:
        return new MovMR(opcode, byte2, byte3);
    case Commands::LEA:
        return new Lea(opcode, byte2, byte3);
    case Commands::JMP:
        return new Jmp(opcode, byte2, byte3);
    case Commands::CMP:
        return new Cmp(opcode, byte2, byte3);
    case Commands::JG:
        return new Jg(opcode, byte2, byte3);
    case Commands::JL:
        return new Jl(opcode, byte2, byte3);
    case Commands::JE:
        return new Je(opcode, byte2, byte3);
    case Commands::CALL:
        return new Call(opcode, byte2, byte3);
    case Commands::RET:
        return new Ret(opcode, byte2, byte3);
    default:
        throw "Unknown command";
    }
}

void In::operator()(VirtualMachine *vm)
{
    int32_t value;
    auto registerNumber = byte2 & 0x0f;
    std::cout << "Program is asking for input: " << std::endl;
    std::cin >> value;
    vm->getProcessor()->setRegisterVal(registerNumber, value);
}

void Out::operator()(VirtualMachine *vm)
{
    auto regNum = byte2 & 0x0f;
    std::cout << "Program output:\n" << vm->getProcessor()->getRegisterVal(regNum) << std::endl;
}

void MovRM::operator()(VirtualMachine *vm)
{
    auto address = vm->getProcessor()->getRegisterVal((byte2 >> 4) & 0x0f);
    uint32_t val = vm->getProcessor()->getRegisterVal(byte2 & 0x0f);
    vm->getMemory()->set(address, val);
}

void MovRR::operator()(VirtualMachine *vm)
{
    uint8_t sourceRegister = byte2 & 0x0f;
    auto sourceRegValue = vm->getProcessor()->getRegisterVal(sourceRegister);
    uint8_t destRegister = (byte2 >> 4) & 0x0f;
    vm->getProcessor()->setRegisterVal(destRegister, sourceRegValue);
}

void MovMR::operator()(VirtualMachine *vm)
{
    auto address = vm->getProcessor()->getRegisterVal(byte2 & 0x0f);
    auto value = vm->getMemory()->get(address);
    vm->getProcessor()->setRegisterVal((byte2 >> 4) & 0x0f, value);
}

void Lea::operator()(VirtualMachine *vm)
{
    auto address = (static_cast<int16_t>(byte2 << 2)) + byte3;
    vm->getProcessor()->setRegisterVal(15, address);
}

void Command::GetValues(VirtualMachine* vm, int32_t &value1, int32_t &value2)
{
    value1 = vm->getProcessor()->getRegisterVal(byte2 & 0x0f); // обнуление старшей половины байта для получения номера первого регистра
    auto address = vm->getProcessor()->getRegisterVal(byte2 >> 4);
    value2 = vm->getMemory()->get32(address); // сдвиг вправо на 4 бита для получения номера второго регистра
}

void Command::GetValues(VirtualMachine *vm, float &value1, float &value2)
{
    Command::Number num1, num2;
    num1.iNum = vm->getProcessor()->getRegisterVal(byte2 & 0x0f); // обнуление старшей половины байта для получения номера первого регистра
    auto address = vm->getProcessor()->getRegisterVal(byte2 >> 4);
    num2.iNum = vm->getMemory()->get32(address); // сдвиг вправо на 4 бита для получения номера второго регистра
    value1 = num1.fNum;
    value2 = num2.fNum;
}

void Add::operator()(VirtualMachine *vm)
{
    int32_t value1, value2;
    GetValues(vm, value1, value2);
    vm->getProcessor()->setRegisterVal(1, value1 + value2);
}

void Sub::operator()(VirtualMachine *vm)
{
    int32_t value1, value2;
    GetValues(vm, value1, value2);
    vm->getProcessor()->setRegisterVal(1, value1 - value2);
}

void Mul::operator()(VirtualMachine *vm)
{
    int32_t value1, value2;
    GetValues(vm, value1, value2);
    vm->getProcessor()->setRegisterVal(1, value1 * value2);
}

void Div::operator()(VirtualMachine *vm)
{
    int32_t value1, value2;
    GetValues(vm, value1, value2);
    if (value2 == 0) {
        throw "Division by zero";
    }
    vm->getProcessor()->setRegisterVal(1, value1 / value2);
}

void Fadd::operator()(VirtualMachine *vm)
{
    float value1, value2;
    GetValues(vm, value1, value2);
    Command::Number result;
    result.fNum =  value1 + value2;
    vm->getProcessor()->setRegisterVal(1, result.iNum);
}

void Fsub::operator()(VirtualMachine *vm)
{
    float value1, value2;
    GetValues(vm, value1, value2);
    Command::Number result;
    result.fNum =  value1 - value2;
    vm->getProcessor()->setRegisterVal(1, result.iNum);
}

void Fmul::operator()(VirtualMachine *vm)
{
    float value1, value2;
    GetValues(vm, value1, value2);
    Command::Number result;
    result.fNum =  value1 * value2;
    vm->getProcessor()->setRegisterVal(1, result.iNum);
}

void Fdiv::operator()(VirtualMachine *vm)
{
    float value1, value2;
    GetValues(vm, value1, value2);
    if (value2 == 0) {
        throw "Division by zero";
    }
    Command::Number result;
    result.fNum = value1 / value2;
    vm->getProcessor()->setRegisterVal(1, result.iNum);
}

void Fin::operator()(VirtualMachine *vm)
{
    Command::Number value;
    auto registerNumber = byte2 & 0x0f;
    std::cout << "\nProgram is asking for input: " << std::endl;
    std::cin >> value.fNum;
    vm->getProcessor()->setRegisterVal(registerNumber, value.iNum);
}

void Fout::operator()(VirtualMachine *vm)
{
    auto regNum = byte2 & 0x0f;
    int32_t ieee = vm->getProcessor()->getRegisterVal(regNum);
    Command::Number value;
    value.iNum = ieee;

    std::cout << std::fixed << "\nProgram output:\n" << value.fNum << std::endl;
}

void Jmp::operator()(VirtualMachine *vm)
{
    uint16_t address = (byte2 << 8) + byte3;
    //std::cout << std::hex << address << std::endl;
    vm->getProcessor()->setIP(address);
}

void Cmp::operator()(VirtualMachine *vm)
{
    int32_t value1, value2;
    GetValues(vm, value1, value2);
    Processor* proc = vm->getProcessor();
    if (value1 == value2) {
        proc->setZF(1);
    } else if (value1 > value2) {
        proc->setZF(0);
        proc->setCF(1);
    } else {
        proc->setZF(0);
        proc->setCF(0);
    }
}

void Jg::operator()(VirtualMachine *vm)
{
    uint8_t zf = vm->getProcessor()->getZF();
    uint8_t cf = vm->getProcessor()->getCF();
    if (cf == 1 && zf == 0) {
        uint16_t address = (byte2 << 8) + byte3;
        vm->getProcessor()->setIP(address);
    }
}

void Jl::operator()(VirtualMachine *vm)
{
    uint8_t zf = vm->getProcessor()->getZF();
    uint8_t cf = vm->getProcessor()->getCF();
    if (cf == 0 && zf == 0) {
        uint16_t address = (byte2 << 8) + byte3;
        vm->getProcessor()->setIP(address);
    }
}

void Je::operator()(VirtualMachine *vm)
{
    uint8_t zf = vm->getProcessor()->getZF();
    if (zf == 1) {
        uint16_t address = (byte2 << 8) + byte3;
        vm->getProcessor()->setIP(address);
    }
}

void Call::operator()(VirtualMachine *vm)
{
    auto currIP = vm->getProcessor()->getIP();
    vm->getProcessor()->setRegisterVal(1, currIP);
    uint16_t address = (byte2 << 8) + byte3;
    vm->getProcessor()->setIP(address);
}

void Ret::operator()(VirtualMachine *vm)
{
    auto address = vm->getProcessor()->getRegisterVal(1);
    vm->getProcessor()->setIP(address);
}
