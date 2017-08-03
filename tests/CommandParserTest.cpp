#include "CommandParserTest.h"

#include <QTest>

#include <list>
#include <string>

#include "CommandParser.h"

using StringList = std::list<std::string>;

void CommandParserTest::parsingIsPossible()
{
    CommandParser p;

    QVERIFY(p.parse({"-a", "1"}) == false);

    p.setOption("-a");

    QVERIFY(p.parse({"-a", "1"}) == true);
    QVERIFY(p.parse({"1", "-a"}) == true);
}
void CommandParserTest::correctParsedArguments()
{
    CommandParser p;
    p.setOption("-a");
    p.setOption("-b");

    p.parse({"arg", "-b", "1", "2", "-a"});

    QVERIFY(p.isSet(""));
    QVERIFY(p.isSet("-a"));
    QVERIFY(p.isSet("-b"));
    QVERIFY(p.isSet("-c") == false);
}
void CommandParserTest::correctParsedValues()
{
    CommandParser p;
    p.setOption("-a");
    p.setOption("-b");

    p.parse({"arg", "-b", "1", "2", "-a"});

    const StringList arg {"arg"};
    QCOMPARE(p.values(""), arg);
    QCOMPARE(p.values("-a"), StringList());
    const StringList b {"1", "2"};
    QCOMPARE(p.values("-b"), b);
    QCOMPARE(p.values("-c"), StringList());
}
