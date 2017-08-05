#pragma once

#include <QObject>

class  ArgsDescTest: public QObject
{
    Q_OBJECT
public:
    explicit ArgsDescTest(QObject * p = 0) : QObject(p) {}

private slots:
    void availableArguments();
    void correctArgumentsValueAndType();
    void descriptionIsFilled();
};
