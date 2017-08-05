#pragma once

#include <QObject>

class AdditionSummatorTest : public QObject
{
    Q_OBJECT
public:
    explicit AdditionSummatorTest(QObject * p = 0) : QObject(p) {}

private slots:
    void checkSumIsValid();
};
