include(../defaults.pri)

CONFIG += console c++11 c++14
CONFIG -= app_bundle

QT += testlib core

TEMPLATE = app

HEADERS += CommandParserTest.h

SOURCES += main.cpp \
        CommandParserTest.cpp

LIBS += -L../src -lWordCounter
