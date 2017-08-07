include(../defaults.pri)

CONFIG += console c++11 c++14
CONFIG -= app_bundle

QT += testlib core

TEMPLATE = app

HEADERS += CommandParserTest.h \
    ArgsDescTest.h \
    AdditionSummatorTest.h \
    FileReaderTest.h \
    WordCounterTest.h

SOURCES += main.cpp \
        CommandParserTest.cpp \
    ArgsDescTest.cpp \
    AdditionSummatorTest.cpp \
    FileReaderTest.cpp \
    WordCounterTest.cpp

LIBS += -L../src -lWordCounter
