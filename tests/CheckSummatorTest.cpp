#include "CheckSummatorTest.h"

#include <QTest>

#include "CheckSummator.h"

void CheckSummatorTest::checkSumIsValid()
{
    CheckSummator summator;
    QVERIFY(summator.checkSum(0) == 0);
    QVERIFY(summator.checkSum(0xDEADBEEF) == 0xDEADBEEF);
    QVERIFY(summator.checkSum(0xBAADF00D) == 0x995BAEFC);
}
