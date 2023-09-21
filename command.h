#ifndef COMMAND_H
#define COMMAND_H

#include <cstdint>
#include <iostream>
#include "virtualmachine.h"

class Command
{    
public:
    Command(int8_t byte1, int8_t byte2, int8_t byte3);
    virtual void operator()(VirtualMachine* vm) = 0;

protected:
    int8_t byte1;
    int8_t byte2;
    int8_t byte3;

};

class In : public Command {
public:
    void operator()(VirtualMachine* vm) override;
};

class Out : public Command {
public:
    void operator()(VirtualMachine* vm) override;
};

class Add : public Command {
public:
    void operator()(VirtualMachine* vm) override;
};

#endif // COMMAND_H
