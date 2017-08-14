#include "FileReaderTest.h"

#include <QTest>

#include <cstdio>
#include <iostream>
#include "FileReader.h"

void FileReaderTest::openFile()
{
    std::ofstream stream("test", std::ofstream::out);
    stream << "text";
    stream.close();
    {
        FileReader<char> fileReader("test", std::ifstream::in);
        QVERIFY(fileReader.isOpened());
    }
    {
        FileReader<char> fileReader("test", std::ifstream::binary);
        QVERIFY(fileReader.isOpened());
    }
    {
        FileReader<char> fileReader("", std::ifstream::in);
        QVERIFY(fileReader.isOpened() == false);
    }
    {
        FileReader<char> fileReader("", std::ifstream::binary);
        QVERIFY(fileReader.isOpened() == false);
    }
    std::remove("test");
}
void FileReaderTest::correctFileLength()
{
    std::ofstream stream("test", std::ofstream::out);
    char data[] = "Hello world, lets test my class!";
    stream << data;
    stream.close();
    const auto size = sizeof(data) - 1; // because of null terminal
    {
        FileReader<char> fileReader("test", std::ifstream::in);
        QVERIFY(fileReader.length() == size);
    }
    {
        FileReader<char> fileReader("test", std::ifstream::binary);
        QVERIFY(fileReader.length() == size);
    }
    std::remove("test");
}
void FileReaderTest::readBuffer()
{
    std::ofstream stream("test", std::ofstream::out);
    std::string input;
    input.append("what a to-do to do to die today");
    input.append("in a minute or two to two");
    input.append("");
    input.append("");
    input.append("lorem ipsum");
    input.append("vice versa");
    input.append("Jason Statham (c)");
    stream << input;
    stream.close();
    {
        FileReader<char> fileReader("test", std::ifstream::in);
        char data[1024] = { 0 };
        const auto size = fileReader.readBuffer(data, 1024);

        QCOMPARE(size, static_cast<int>(input.size()));
        std::string str(data);
        QCOMPARE(str, input);
    }
    std::remove("test");
}
