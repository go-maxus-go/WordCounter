#pragma once

#include <QObject>

class ArgsParserTest : public QObject
{
    Q_OBJECT
public:
    explicit ArgsParserTest(QObject * p = 0) : QObject(p) {}

private slots:
    void parsingIsPossible();
    void correctParsedArguments();
    void correctParsedValues();
};
