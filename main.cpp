#include <iostream>
#include <cstdint>
#include <fstream>
#include <bitset>
#include <vector>

using namespace std;

enum Commands {
    MOVRR = 0x01,
    MOVMR = 0x02,
    MOVRM = 0x03,
    ADD = 0x04,
    SUB = 0x05,
    MUL = 0x06,
    DIV = 0x07,
    FADD = 0x08,
    FSUB = 0x09,
    FMUL = 0x0a,
    FDIV = 0x0b,
    JMP = 0x0c,
    RELJMP = 0x0d,
    INDJMP = 0x0e,
    JE = 0x0f,
    JNE = 0x10,
    JG = 0x11,
    JGE = 0x12,
    JL = 0x13,
    JLE = 0x14,
    CALL = 0x15,
    RET = 0x16,
    IN = 0x17,
    OUT = 0x18,
    HALT = 0x19
};

uint32_t PSW;
int8_t memory[65536];
// 0-16383 reserved for code. 16384 - first available address (0x4000)
int32_t registers[16];
int count = 0;

/*
1 - movrr 0000001 0x01
2 - movmr 0000010 0x02
3 - movrm 0000011 0x03
4 - add 0000100 0x04
5 - sub 0000101 0x05
6 - mul 0000110 0x06
7 - div 0000111 0x07
8 - fadd 0001000 0x08
9 - fsub 0001001 0x09
10 - fmul 0001010 0x0a
11 - fdiv 0001011 0x0b
12 - jmp 0001100 0x0c
13 - reljmp 0001101 0x0d
14 - indjmp 0001110 0x0e
15 - je - jump if equal 0001111 0x0f
16 - jne - jump if not equal 0010000 0x10
17 - jg - jump if greater 0010001 0x11
18 - jge - jump if greater or equal 0010010 0x12
19 - jl - jump if less 0010011 0x13
20 - jle - jump if less or equal 0010100 0x14
21 - call 0010101 0x15
22 - ret 0010110 0x16
23 - in 0010111 0x17
24 - out 0011000 0x18
25 - halt 0011001 0x19
*/

void load(string filename) {
    fstream file;
    file.open(filename);
    string str;
    while (file >> str) {
        memory[count] = stoi(str, nullptr,16);
        count++;
    }
    memory[count] = Commands::HALT;
    count++;
    memory[count] = 0;
    count++;
    memory[count] = 0;
    file.close();

}

uint16_t getIP() {
    return PSW >> 16;
}

void setIP(uint16_t address) {
    int32_t newaddr = address << 16;
    PSW &= 0xffff;
    PSW += newaddr;
}

int32_t getRegister(int number) {
    return registers[number - 1];
}

void setRegister(int number, int32_t value) {
    registers[number - 1] = value;
}

void doIn(int8_t arg1, int8_t arg2) {
    int32_t value;
    auto registerNumber = arg1 & 0x0f;
    cout << "Program is asking for input: " << endl;
    cin >> value;
    //cout << "arg1 " << static_cast<int>(arg1) << endl;
    setRegister(registerNumber, value);
}

void doOut(int8_t arg1, int8_t arg2) {
    auto registerNumber = arg1 & 0x0f;
    cout << "Program output:\n" << getRegister(registerNumber) << endl;
}

void add(int8_t arg1, int8_t arg2) {
    auto value1 = getRegister(arg1 & 0x0f);
    auto value2 = getRegister(arg1 >> 4);
    setRegister(1, value1 + value2);
}

void run() {
    int8_t opcode = 0, arg1, arg2;
    int ip = getIP();
    while (opcode != Commands::HALT) {
        opcode = memory[ip++];
        arg1 = memory[ip++];
        arg2 = memory[ip++];
        //cout << "opcode " << static_cast<int>(opcode) << endl;
        switch(opcode) {
        case Commands::IN:
            doIn(arg1, arg2);
            break;
        case Commands::OUT:
            doOut(arg1, arg2);
            break;
        case Commands::ADD:
            add(arg1, arg2);
        }
    }


//    while(file >> hex >> first >> second >> third) {
//        cout << hex << first << " " << second << " " << third << endl;
//        int8_t d = first & 0x80;
//        int8_t opcode = first & 0x7f;
//        cout << hex << "d: " << static_cast<int>(d) << endl << "opcode: " << static_cast<int>(opcode) << endl;
//    }
}

int main()
{
    load("C:\\Users\\nel\\Documents\\QtProjects\\vm\\input.txt");
    setIP(0);
    run();


    return 0;
}
