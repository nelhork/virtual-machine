#include <iostream>
#include <cstdint>
#include <fstream>
#include <bitset>
#include <vector>
#include <command.h>

using namespace std;

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

uint32_t PSW;
int8_t memory[65536];
// 0-16383 reserved for code. 16384 - first available address (0x4000)
int32_t registers[16];

void load(string filename) {
    int count = 0;
    fstream file;
    file.open(filename);
    string str;
    while (file >> str) {
        memory[count] = stoi(str, nullptr,16); // перевод из строки в шестнадцатеричное число
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
    return registers[number];
}

void setRegister(int number, int32_t value) {
    registers[number] = value;
}

void doIn(int8_t byte2) {
    int32_t value;
    auto registerNumber = byte2 & 0x0f;
    cout << "Program is asking for input: " << endl;
    cin >> value;
    //cout << "arg1 " << static_cast<int>(arg1) << endl;
    setRegister(registerNumber, value);
}

void doOut(int8_t byte2) {
    auto regNum = byte2 & 0x0f;
    cout << "Program output:\n" << getRegister(regNum) << endl;
}

void add(int8_t byte2) {
    auto value1 = getRegister(byte2 & 0x0f); // обнуление старшей половины байта для получения номера первого регистра
    auto value2 = memory[getRegister(byte2 >> 4)]; // сдвиг вправо на 4 бита для получения номера второго регистра
    setRegister(1, value1 + value2);
}

void lea(int8_t byte2, int8_t byte3) {
    auto address = ((byte2 << 2) & 0xf0) + byte3;
    setRegister(15, address);
}

void movrm(int8_t regnum) {
    memory[getRegister((regnum >> 4) & 0x0f)] = getRegister(regnum & 0x0f);
}

void run() {
    int8_t opcode = 0, byte2, byte3;
    int ip = getIP();
    while (opcode != Commands::HALT) {
        opcode = memory[ip++];
        byte2 = memory[ip++];
        byte3 = memory[ip++];
        //cout << "opcode " << static_cast<int>(opcode) << endl;
        switch(opcode) {
        case Commands::IN:
            doIn(byte2);
            break;
        case Commands::OUT:
            doOut(byte2);
            break;
        case Commands::ADD:
            add(byte2);
            break;
        case Commands::MOVRM:
            movrm(byte2);
            break;
        case Commands::LEA:
            lea(byte2, byte3);
        }
    }
}

int main()
{
    load("C:\\Users\\nel\\Documents\\QtProjects\\vm\\input.txt");
    setIP(0);
    run();

    Command command;

    return 0;
}
