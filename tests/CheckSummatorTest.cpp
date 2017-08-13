#include "CheckSummatorTest.h"

#include <QTest>

#include "CheckSummator.h"

void CheckSummatorTest::checkSumForSingleNumber()
{
    CheckSummator summator;
    QVERIFY(summator.checkSum(0) == 0);
    QVERIFY(summator.checkSum(0xDEADBEEF) == 0xDEADBEEF);
    QVERIFY(summator.checkSum(0xBAADF00D) == 0x995BAEFC);
}
void CheckSummatorTest::checkSumForBuffer()
{
    CheckSummator summator;
    uint8_t data0[] = {0, 1, 2, 3};
    QVERIFY(summator.checkSum(data0, 4) == 0x00010203);
    uint8_t data1[] = {0, 1, 2, 3, 4, 5, 6, 7};
    QVERIFY(summator.checkSum(data1, 8) == 0x04070A0D);
    uint8_t data2[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    QVERIFY(summator.checkSum(data2, 10) == 0x080D1A20);
}
