include(../defaults.pri)

CONFIG   += console c++11 c++14
CONFIG   -= app_bundle
CONFIG   -= qt

TEMPLATE = lib

TARGET = WordCounter

HEADERS += CommandParser.h
SOURCES += CommandParser.cpp
