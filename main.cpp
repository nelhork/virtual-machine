#include <iostream>
#include <fstream>
#include "processor.h"

Processor processor;

void load(std::string filename) { // загрузка значений из файла в память
    int memoryAddress = 0; // индекс массива памяти
    std::string strMemoryAddress;
    std::fstream instructionFile;
    instructionFile.open(filename, std::ios::binary | std::ios::in);
    // instructionFile >> strMemoryAddress;
    int startAddress = 0; // std::stoi(strMemoryAddress, nullptr, 16);
    memoryAddress = startAddress;
    //std::string str;
    char byte;
    while (instructionFile.read(&byte, 1)) {
        processor.getMemory().set(memoryAddress, static_cast<uint8_t>(byte));
        memoryAddress++;
    }
    instructionFile.close();

    processor.setIP(startAddress);
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cout << "Error: program path is not specified\n";
        return -1;
    }
    load(argv[1]);
    processor.run();

    return 0;
}
