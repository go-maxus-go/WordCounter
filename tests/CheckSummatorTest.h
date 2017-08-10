#pragma once

#include <QObject>

class CheckSummatorTest : public QObject
{
    Q_OBJECT
public:
    explicit CheckSummatorTest(QObject * p = 0) : QObject(p) {}

private slots:
    void checkSumForSingleNumber();
    void checkSumForBuffer();
};
