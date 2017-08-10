#include "WordCounterTest.h"

#include <QTest>

#include "WordCounter.h"

void WordCounterTest::correctCount()
{
    WordCounter counter("hi");
    QCOMPARE(counter.count(), 0UL);

    counter.process("hi my name is Maxim");
    QCOMPARE(counter.count(), 1UL);

    counter.process("qwe hi qwe");
    QCOMPARE(counter.count(), 2UL);

    counter.process("qwe hi");
    QCOMPARE(counter.count(), 3UL);

    counter.process("hi hi hi qq");
    QCOMPARE(counter.count(), 6UL);

    counter.process("qwe h");
    counter.process("i qwe");
    QCOMPARE(counter.count(), 7UL);
}
void WordCounterTest::falseCount()
{
    WordCounter counter("hello");

    counter.process("qwe hel");
    counter.process(" lo qwe");
    QCOMPARE(counter.count(), 0UL);

    counter.process("qwe hel ");
    counter.process("lo qwe");
    QCOMPARE(counter.count(), 0UL);

    counter.process("qwe hel ");
    counter.process(" lo qwe");
    QCOMPARE(counter.count(), 0UL);
}
void WordCounterTest::caseInsensitive()
{
    WordCounter counter("Hello");

    counter.process("hello");
    QCOMPARE(counter.count(), 1UL);
}
void WordCounterTest::anotherLanguage()
{
    // TODO: support encodings, better use QString in future
    //WordCounter counter("привет");

    //counter.process("Привет привет приВЕТ");
    //QCOMPARE(counter.count(), 3UL);
}
