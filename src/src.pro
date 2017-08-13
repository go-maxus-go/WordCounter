include(../defaults.pri)

CONFIG   += console c++11 c++14
CONFIG   -= app_bundle
CONFIG   -= qt

TEMPLATE = lib

TARGET = WordCounter

HEADERS += ArgsParser.h \
    ArgsDesc.h \
    CheckSummator.h \
    FileReader.h \
    WordCounter.h \
    Commander.h
SOURCES += ArgsParser.cpp \
    ArgsDesc.cpp \
    CheckSummator.cpp \
    FileReader.cpp \
    WordCounter.cpp \
    Commander.cpp
