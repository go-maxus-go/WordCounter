#include "WordCounterTest.h"

#include <QTest>

#include "WordCounter.h"

void WordCounterTest::correctCount()
{
    WordCounter counter(L"hi");
    QCOMPARE(counter.count(), 0UL);

    counter.process(L"hi my name is Maxim");
    QCOMPARE(counter.count(), 1UL);

    counter.process(L"qwe hi qwe");
    QCOMPARE(counter.count(), 2UL);

    counter.process(L"qwe hi");
    QCOMPARE(counter.count(), 3UL);

    counter.process(L"hi hi hi qq");
    QCOMPARE(counter.count(), 6UL);

    counter.process(L"qwe h");
    counter.process(L"i qwe");
    QCOMPARE(counter.count(), 7UL);

    counter.process(L"qwe hiqw");
    counter.process(L"qwei qwe");
    QCOMPARE(counter.count(), 8UL);
}
void WordCounterTest::falseCount()
{
    WordCounter counter(L"hello");

    counter.process(L"qwe hel");
    counter.process(L" lo qwe");
    QCOMPARE(counter.count(), 0UL);

    counter.process(L"qwe hel ");
    counter.process(L"lo qwe");
    QCOMPARE(counter.count(), 0UL);

    counter.process(L"qwe hel ");
    counter.process(L" lo qwe");
    QCOMPARE(counter.count(), 0UL);
}
void WordCounterTest::caseInsensitive()
{
    WordCounter counter(L"Hello");

    counter.process(L"hello");
    QCOMPARE(counter.count(), 1UL);
}
void WordCounterTest::anotherLanguage()
{
    WordCounter counter(L"привет");

    counter.process(L"Привет привет приВЕТ");
    QCOMPARE(counter.count(), 3UL);

    counter.process(L"При ");
    counter.process(L"вет ");
    counter.process(L" При");
    counter.process(L" вет");
    counter.process(L" При ");
    counter.process(L" вет ");
    QCOMPARE(counter.count(), 3UL);
}
