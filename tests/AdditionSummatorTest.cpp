#include "AdditionSummatorTest.h"

#include <QTest>

#include "AdditionSummator.h"

void AdditionSummatorTest::checkSumIsValid()
{
    AdditionSummator summator;
    QVERIFY(summator.checkSum(0) == 0);
    QVERIFY(summator.checkSum(0xDEADBEEF) == 0xDEADBEEF);
    QVERIFY(summator.checkSum(0xBAADF00D) == 0x995BAEFC);
}
