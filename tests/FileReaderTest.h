#pragma once

#include <QObject>

class FileReaderTest : public QObject
{
    Q_OBJECT
public:
    explicit FileReaderTest(QObject * p = 0) : QObject(p) {}

private slots:
    void openFile();
    void correctFileLength();
    void readBuffer();
};
