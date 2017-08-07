#include <iostream>

#include "CommandParser.h"
#include "ArgsDesc.h"
#include "ICheckSummator.h"
#include "FileReader.h"
#include "WordCounter.h"

int main(int argc, char *argv[])
{
    CommandParser p;
    ArgsDesc::get().args();

    auto summator = createCheckSummator();

    std::cout << summator->checkSum(42) << std::endl;
    FileReader fileReader("", std::ifstream::in);

    WordCounter counter("hello");

    std::cout << "Hello 2gis!" << std::endl;

    return 0;
}
