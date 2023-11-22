#include "command.h"

Command::Command(uint8_t byte1, uint8_t byte2, uint8_t byte3)
{
    this->byte1 = byte1;
    this->byte2 = byte2;
    this->byte3 = byte3;
}

Command* Command::getCommand(uint8_t opcode, uint8_t byte2, uint8_t byte3)
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

void In::operator()(Processor*vm)
{
    int32_t value;
    auto registerNumber = byte2 & 0x0f;
    std::cin >> value;
    vm->registers[registerNumber] = value;
}

void Out::operator()(Processor*vm)
{
    auto regNum = byte2 & 0x0f;
    std::cout << vm->registers[regNum] << std::endl;
}

void MovRM::operator()(Processor*vm)
{
    auto address = vm->registers[(byte2 >> 4) & 0x0f];
    uint32_t val = vm->registers[byte2 & 0x0f];
    vm->getMemory().set(address, val);
}

void MovRR::operator()(Processor*vm)
{
    uint8_t sourceRegister = byte2 & 0x0f;
    auto sourceRegValue = vm->registers[sourceRegister];
    uint8_t destRegister = (byte2 >> 4) & 0x0f;
    vm->registers[destRegister] = sourceRegValue;
}

void MovMR::operator()(Processor* vm)
{
    auto address = vm->registers[byte2 & 0x0f];
    auto value = vm->getMemory().get(address);
    vm->registers[(byte2 >> 4) & 0x0f] = value;
}

void Lea::operator()(Processor* vm)
{
    auto address = (static_cast<int16_t>(byte2 << 2)) + byte3;
    vm->registers[15] = address;
}

void Command::GetValues(Processor* vm, int32_t &value1, int32_t &value2)
{
    value1 = vm->registers[byte2 & 0x0f]; // обнуление старшей половины байта для получения номера первого регистра
    auto address = vm->registers[byte2 >> 4];
    value2 = vm->getMemory().get32(address); // сдвиг вправо на 4 бита для получения номера второго регистра
}

void Command::GetValues(Processor*vm, float &value1, float &value2)
{
    Command::Number num1, num2;
    num1.iNum = vm->registers[byte2 & 0x0f]; // обнуление старшей половины байта для получения номера первого регистра
    auto address = vm->registers[byte2 >> 4];
    num2.iNum = vm->getMemory().get32(address); // сдвиг вправо на 4 бита для получения номера второго регистра
    value1 = num1.fNum;
    value2 = num2.fNum;
}

void Add::operator()(Processor*vm)
{
    int32_t value1, value2;
    GetValues(vm, value1, value2);
    vm->registers[1] = value1 + value2;
}

void Sub::operator()(Processor*vm)
{
    int32_t value1, value2;
    GetValues(vm, value1, value2);
    vm->registers[1] = value1 - value2;
}

void Mul::operator()(Processor*vm)
{
    int32_t value1, value2;
    GetValues(vm, value1, value2);
    vm->registers[1] = value1 * value2;
}

void Div::operator()(Processor*vm)
{
    int32_t value1, value2;
    GetValues(vm, value1, value2);
    if (value2 == 0) {
        throw "Division by zero";
    }
    vm->registers[1] = value1 / value2;
}

void Fadd::operator()(Processor*vm)
{
    float value1, value2;
    GetValues(vm, value1, value2);
    Command::Number result;
    result.fNum =  value1 + value2;
    vm->registers[1] = result.iNum;
}

void Fsub::operator()(Processor*vm)
{
    float value1, value2;
    GetValues(vm, value1, value2);
    Command::Number result;
    result.fNum =  value1 - value2;
    vm->registers[1] = result.iNum;
}

void Fmul::operator()(Processor*vm)
{
    float value1, value2;
    GetValues(vm, value1, value2);
    Command::Number result;
    result.fNum =  value1 * value2;
    vm->registers[1] = result.iNum;
}

void Fdiv::operator()(Processor*vm)
{
    float value1, value2;
    GetValues(vm, value1, value2);
    if (value2 == 0) {
        throw "Division by zero";
    }
    Command::Number result;
    result.fNum = value1 / value2;
    vm->registers[1] = result.iNum;
}

void Fin::operator()(Processor*vm)
{
    Command::Number value;
    auto registerNumber = byte2 & 0x0f;
    std::cin >> value.fNum;
    vm->registers[registerNumber] = value.iNum;
}

void Fout::operator()(Processor*vm)
{
    auto regNum = byte2 & 0x0f;
    int32_t ieee = vm->registers[regNum];
    Command::Number value;
    value.iNum = ieee;

    std::cout << std::fixed << value.fNum << std::endl;
}

void Jmp::operator()(Processor*vm)
{
    uint16_t address = (byte2 << 8) + byte3;
    vm->setIP(address);
}

void Cmp::operator()(Processor*vm)
{
    int32_t value1, value2;
    GetValues(vm, value1, value2);
    Processor* proc = vm;
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

void Jg::operator()(Processor*vm)
{
    uint8_t zf = vm->getZF();
    uint8_t cf = vm->getCF();
    if (cf == 1 && zf == 0) {
        uint16_t address = (byte2 << 8) + byte3;
        vm->setIP(address);
    }
}

void Jl::operator()(Processor*vm)
{
    uint8_t zf = vm->getZF();
    uint8_t cf = vm->getCF();
    if (cf == 0 && zf == 0) {
        uint16_t address = (byte2 << 8) + byte3;
        vm->setIP(address);
    }
}

void Je::operator()(Processor*vm)
{
    uint8_t zf = vm->getZF();
    if (zf == 1) {
        uint16_t address = (byte2 << 8) + byte3;
        vm->setIP(address);
    }
}

void Call::operator()(Processor*vm)
{
    auto currIP = vm->getIP();
    vm->registers[1] = currIP;
    uint16_t address = (byte2 << 8) + byte3;
    vm->setIP(address);
}

void Ret::operator()(Processor*vm)
{
    auto address = vm->registers[1];
    vm->setIP(address);
}
