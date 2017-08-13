#pragma once

#include <QObject>

class WordCounterTest : public QObject
{
    Q_OBJECT
public:
    explicit WordCounterTest(QObject * p = 0) : QObject(p) {}

private slots:
    void correctCount();
    void falseCount();
    void caseInsensitive();
    void anotherLanguage();
};
