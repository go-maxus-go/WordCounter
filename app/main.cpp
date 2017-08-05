#include <iostream>

#include "CommandParser.h"
#include "ArgsDesc.h"
#include <ICheckSummator.h>

int main(int argc, char *argv[])
{
    CommandParser p;
    ArgsDesc::get().args();

    auto summator = createCheckSummator();

    std::cout << summator->checkSum(42) << std::endl;

    std::cout << "Hello 2gis!" << std::endl;

    return 0;
}
