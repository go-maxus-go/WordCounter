include(../defaults.pri)

CONFIG   += console c++11 c++14
CONFIG   -= app_bundle
CONFIG   -= qt

TEMPLATE = lib

TARGET = WordCounter

HEADERS += CommandParser.h \
    ArgsDesc.h \
    CheckSummator.h \
    FileReader.h \
    WordCounter.h \
    Commander.h \
    Application.h
SOURCES += CommandParser.cpp \
    ArgsDesc.cpp \
    CheckSummator.cpp \
    FileReader.cpp \
    WordCounter.cpp \
    Commander.cpp \
    Application.cpp
