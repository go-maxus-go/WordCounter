#include <QtTest>
#include <QCoreApplication>

#include "CommandParserTest.h"
#include "ArgsDescTest.h"
#include "AdditionSummatorTest.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTest::qExec(new CommandParserTest    , argc, argv);
    QTest::qExec(new ArgsDescTest         , argc, argv);
    QTest::qExec(new AdditionSummatorTest , argc, argv);

    return 0;
}
