#pragma once

#include <QObject>

class CommandParserTest : public QObject
{
    Q_OBJECT
public:
    explicit CommandParserTest(QObject * p = 0) : QObject(p) {}

private slots:
    void parsingIsPossible();
    void correctParsedArguments();
    void correctParsedValues();
};
