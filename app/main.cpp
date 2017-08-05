#include <iostream>

#include "CommandParser.h"
#include "ArgsDesc.h"

int main(int argc, char *argv[])
{
    CommandParser p;
    ArgsDesc::get().args();

    std::cout << "Hello 2gis!" << std::endl;

    return 0;
}
