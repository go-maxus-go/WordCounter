#include <QtTest>
#include <QCoreApplication>

#include "CommandParserTest.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTest::qExec(new CommandParserTest, argc, argv);

    return 0;
}
