include(../defaults.pri)

CONFIG += console c++11 c++14
CONFIG -= app_bundle

QT += testlib core

TEMPLATE = app

HEADERS += CommandParserTest.h \
    ArgsDescTest.h \
    FileReaderTest.h \
    WordCounterTest.h \
    CheckSummatorTest.h

SOURCES += main.cpp \
        CommandParserTest.cpp \
    ArgsDescTest.cpp \
    FileReaderTest.cpp \
    WordCounterTest.cpp \
    CheckSummatorTest.cpp

LIBS += -L../src -lWordCounter
