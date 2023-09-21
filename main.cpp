#include "command.h"
#include "virtualmachine.h"

int main()
{
    VirtualMachine vm;
    vm.load("C:\\Users\\nel\\Documents\\QtProjects\\vm\\input.txt");
    vm.run();

    return 0;
}
