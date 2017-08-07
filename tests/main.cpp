#include <QtTest>
#include <QCoreApplication>

#include "CommandParserTest.h"
#include "ArgsDescTest.h"
#include "AdditionSummatorTest.h"
#include "FileReaderTest.h"
#include "WordCounterTest.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTest::qExec(new CommandParserTest    , argc, argv);
    QTest::qExec(new ArgsDescTest         , argc, argv);
    QTest::qExec(new AdditionSummatorTest , argc, argv);
    QTest::qExec(new FileReaderTest       , argc, argv);
    QTest::qExec(new WordCounterTest      , argc, argv);

    return 0;
}
