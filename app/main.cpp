#include <locale>

#include "Application.h"

int main(int argc, char *argv[])
{
    std::locale::global(std::locale("en_US.UTF-8"));

    Application app(argc, argv);
    return app.exec();
}
