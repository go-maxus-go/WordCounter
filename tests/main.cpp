#include <QtTest>
#include <QCoreApplication>

#include <locale>

#include "ArgsDescTest.h"
#include "FileReaderTest.h"
#include "WordCounterTest.h"
#include "CheckSummatorTest.h"
#include "ArgsParserTest.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::locale::global(std::locale("en_US.UTF-8"));

    QTest::qExec(new ArgsDescTest     , argc, argv);
    QTest::qExec(new FileReaderTest   , argc, argv);
    QTest::qExec(new ArgsParserTest   , argc, argv);
    QTest::qExec(new WordCounterTest  , argc, argv);
    QTest::qExec(new CheckSummatorTest, argc, argv);

    return 0;
}
