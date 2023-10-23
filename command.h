#ifndef COMMAND_H
#define COMMAND_H

#include <cstdint>
#include <iostream>
#include "virtualmachine.h"

class Command
{    
public:
    Command(uint8_t byte1, uint8_t byte2, uint8_t byte3);
    virtual void operator()(VirtualMachine* vm) = 0;
    static Command* getCommand(uint8_t opcode, uint8_t byte2, uint8_t byte3);

protected:
    union Number {
        uint32_t iNum;
        float fNum;
    };

    uint8_t byte1;
    uint8_t byte2;
    uint8_t byte3;

    void GetValues(VirtualMachine* vm, int32_t &value1, int32_t &value2);
    void GetValues(VirtualMachine* vm, float &value1, float &value2);
};

class In : public Command {
public:
    In(uint8_t byte1, uint8_t byte2, uint8_t byte3) : Command(byte1, byte2, byte3) {}
    void operator()(VirtualMachine* vm) override;
};

class Out : public Command {
public:
    Out(uint8_t byte1, uint8_t byte2, uint8_t byte3) : Command(byte1, byte2, byte3) {}
    void operator()(VirtualMachine* vm) override;
};

class Add : public Command {
public:
    Add(uint8_t byte1, uint8_t byte2, uint8_t byte3) : Command(byte1, byte2, byte3) {}
    void operator()(VirtualMachine* vm) override;
};

class Sub : public Command {
public:
    Sub(uint8_t byte1, uint8_t byte2, uint8_t byte3) : Command(byte1, byte2, byte3) {}
    void operator()(VirtualMachine* vm) override;
};

class Mul : public Command {
public:
    Mul(uint8_t byte1, uint8_t byte2, uint8_t byte3) : Command(byte1, byte2, byte3) {}
    void operator()(VirtualMachine* vm) override;
};

class Div : public Command {
public:
    Div(uint8_t byte1, uint8_t byte2, uint8_t byte3) : Command(byte1, byte2, byte3) {}
    void operator()(VirtualMachine* vm) override;
};

class Fadd : public Command {
public:
    Fadd(uint8_t byte1, uint8_t byte2, uint8_t byte3) : Command(byte1, byte2, byte3) {}
    void operator()(VirtualMachine* vm) override;
};

class Fsub : public Command {
public:
    Fsub(uint8_t byte1, uint8_t byte2, uint8_t byte3) : Command(byte1, byte2, byte3) {}
    void operator()(VirtualMachine* vm) override;
};

class Fmul : public Command {
public:
    Fmul(uint8_t byte1, uint8_t byte2, uint8_t byte3) : Command(byte1, byte2, byte3) {}
    void operator()(VirtualMachine* vm) override;
};

class Fdiv : public Command {
public:
    Fdiv(uint8_t byte1, uint8_t byte2, uint8_t byte3) : Command(byte1, byte2, byte3) {}
    void operator()(VirtualMachine* vm) override;
};

class Fin : public Command {
public:
    Fin(uint8_t byte1, uint8_t byte2, uint8_t byte3) : Command(byte1, byte2, byte3) {}
    void operator()(VirtualMachine* vm) override;
};

class Fout : public Command {
public:
    Fout(uint8_t byte1, uint8_t byte2, uint8_t byte3) : Command(byte1, byte2, byte3) {}
    void operator()(VirtualMachine* vm) override;
};

class MovRM : public Command {
public:
    MovRM(uint8_t byte1, uint8_t byte2, uint8_t byte3) : Command(byte1, byte2, byte3) {}
    void operator()(VirtualMachine* vm) override;
};

class MovRR : public Command {
public:
    MovRR(uint8_t byte1, uint8_t byte2, uint8_t byte3) : Command(byte1, byte2, byte3) {}
    void operator()(VirtualMachine* vm) override;
};

class MovMR : public Command {
public:
    MovMR(uint8_t byte1, uint8_t byte2, uint8_t byte3) : Command(byte1, byte2, byte3) {}
    void operator()(VirtualMachine* vm) override;
};


class Lea : public Command {
public:
    Lea(uint8_t byte1, uint8_t byte2, uint8_t byte3) : Command(byte1, byte2, byte3) {}
    void operator()(VirtualMachine* vm) override;
};

class Jmp : public Command {
public:
    Jmp(uint8_t byte1, uint8_t byte2, uint8_t byte3) : Command(byte1, byte2, byte3) {}
    void operator()(VirtualMachine* vm) override;
};

class Cmp : public Command {
public:
    Cmp(uint8_t byte1, uint8_t byte2, uint8_t byte3) : Command(byte1, byte2, byte3) {}
    void operator()(VirtualMachine* vm) override;
};

class Jg : public Command {
public:
    Jg(uint8_t byte1, uint8_t byte2, uint8_t byte3) : Command(byte1, byte2, byte3) {}
    void operator()(VirtualMachine* vm) override;
};

class Jl : public Command {
public:
    Jl(uint8_t byte1, uint8_t byte2, uint8_t byte3) : Command(byte1, byte2, byte3) {}
    void operator()(VirtualMachine* vm) override;
};

class Je : public Command {
public:
    Je(uint8_t byte1, uint8_t byte2, uint8_t byte3) : Command(byte1, byte2, byte3) {}
    void operator()(VirtualMachine* vm) override;
};

class Call : public Command {
public:
    Call(uint8_t byte1, uint8_t byte2, uint8_t byte3) : Command(byte1, byte2, byte3) {}
    void operator()(VirtualMachine* vm) override;
};

class Ret : public Command {
public:
    Ret(uint8_t byte1, uint8_t byte2, uint8_t byte3) : Command(byte1, byte2, byte3) {}
    void operator()(VirtualMachine* vm) override;
};

enum Commands {
    MOVRR = 0x01, // 00000001 +
    MOVMR = 0x02, // 00000010
    MOVRM = 0x03, // 00000011 +

    ADD = 0x10, // 00010000 +
    SUB = 0x11, // 00010001 +
    MUL = 0x12, // 00010010 +
    DIV = 0x13, // 00010011 +

    FADD = 0x20, // 00100000 +
    FSUB = 0x21, // 00100001 +
    FMUL = 0x22, // 00100010 +
    FDIV = 0x23, // 00100011 +
    FIN = 0x24, // 00100100 +
    FOUT = 0x25, // 00100101 +

    JMP = 0x30, // 00110000 +
    //RELJMP = 0x31, // 00110001
    //INDJMP = 0x32, // 00110010
    JE = 0x33, // 00110011 +
    //JNE = 0x34, // 00110100
    JG = 0x35, // 00110101 +
    //JGE = 0x36, // 00110110
    JL = 0x37, // 00110111 +
    //JLE = 0x38, // 00111000

    LEA = 0x40, // 01000000 + загружает адрес ячейки памяти в r16

    CALL = 0x50, // 01010000 +
    RET = 0x51, // 01010001 +
    IN = 0x52, // 01010010 +
    OUT = 0x53, // 01010011 +
    HALT = 0x54, // 01010100 +

    CMP = 0x60 // 01100000 + op1 = op2: ZF = 1; op1 > op2: CF = 1, ZF = 0; op1 < op2: ZF = 0, CF = 0
};

#endif // COMMAND_H
