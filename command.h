#ifndef COMMAND_H
#define COMMAND_H

#include <cstdint>
#include <iostream>
#include "virtualmachine.h"

class Command
{    
    friend class VirtualMachine;
public:

    Command(int8_t byte1, int8_t byte2, int8_t byte3);
    virtual void operator()(VirtualMachine* vm) = 0;
    static Command* getCommand(int8_t opcode, int8_t byte2, int8_t byte3);

protected:
    int8_t byte1;
    int8_t byte2;
    int8_t byte3;

};

class In : public Command {
public:
    In(int8_t byte1, int8_t byte2, int8_t byte3) : Command(byte1, byte2, byte3) {}
    void operator()(VirtualMachine* vm) override;
};

class Out : public Command {
public:
    Out(int8_t byte1, int8_t byte2, int8_t byte3) : Command(byte1, byte2, byte3) {}
    void operator()(VirtualMachine* vm) override;
};

class Add : public Command {
public:
    Add(int8_t byte1, int8_t byte2, int8_t byte3) : Command(byte1, byte2, byte3) {}
    void operator()(VirtualMachine* vm) override;
};

class MovRM : public Command {
public:
    MovRM(int8_t byte1, int8_t byte2, int8_t byte3) : Command(byte1, byte2, byte3) {}
    void operator()(VirtualMachine* vm) override;
};

class Lea : public Command {
public:
    Lea(int8_t byte1, int8_t byte2, int8_t byte3) : Command(byte1, byte2, byte3) {}
    void operator()(VirtualMachine* vm) override;
};

enum Commands {
    MOVRR = 0x01, // 00000001
    MOVMR = 0x02, // 00000010
    MOVRM = 0x03, // 00000011

    ADD = 0x10, // 00010000
    SUB = 0x11, // 00010001
    MUL = 0x12, // 00010010
    DIV = 0x13, // 00010011

    FADD = 0x20, // 00100000
    FSUB = 0x21, // 00100001
    FMUL = 0x22, // 00100010
    FDIV = 0x23, // 00100011

    JMP = 0x30, // 00110000
    RELJMP = 0x31, // 00110001
    INDJMP = 0x32, // 00110010
    JE = 0x33, // 00110011
    JNE = 0x34, // 00110100
    JG = 0x35, // 00110101
    JGE = 0x36, // 00110110
    JL = 0x37, // 00110111
    JLE = 0x38, // 00111000

    LEA = 0x40, // 01000000 загружает адрес ячейки памяти в r16

    CALL = 0x50, // 01010000
    RET = 051, // 01010001
    IN = 0x52, // 01010010
    OUT = 0x53, // 01010011
    HALT = 0x54 // 01010100
};

#endif // COMMAND_H
