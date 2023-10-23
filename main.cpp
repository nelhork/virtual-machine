#include "virtualmachine.h"
#include <iostream>

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cout << "Error: program path is not specified\n";
        return -1;
    }
    VirtualMachine vm;
    vm.load(argv[1]);
    vm.run();

    return 0;
}
