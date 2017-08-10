#include <QtTest>
#include <QCoreApplication>

#include "ArgsDescTest.h"
#include "FileReaderTest.h"
#include "WordCounterTest.h"
#include "CheckSummatorTest.h"
#include "CommandParserTest.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTest::qExec(new CommandParserTest    , argc, argv);
    QTest::qExec(new ArgsDescTest         , argc, argv);
    QTest::qExec(new CheckSummatorTest , argc, argv);
    QTest::qExec(new FileReaderTest       , argc, argv);
    QTest::qExec(new WordCounterTest      , argc, argv);

    return 0;
}
