include(../defaults.pri)

CONFIG   += console c++11 c++14
CONFIG   -= app_bundle
CONFIG   -= qt

TEMPLATE = lib

TARGET = WordCounter

HEADERS += CommandParser.h \
    ArgsDesc.h \
    ICheckSummator.h \
    AdditionSummator.h
SOURCES += CommandParser.cpp \
    ArgsDesc.cpp \
    ICheckSummator.cpp
