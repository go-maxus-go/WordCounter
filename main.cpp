#include <string>
#include <iostream>

int main(int argc, char *argv[])
{
    for (int i = 0; i < argc; ++i)
        std::cout << std::string(argv[i]) << std::endl;
    return 0;
}
