include(../defaults.pri)

CONFIG += console c++11 c++14
CONFIG -= app_bundle
CONFIG -= qt

TEMPLATE = app

HEADERS += Application.h

SOURCES += main.cpp \
    Application.cpp

LIBS += -L../src -lWordCounter

HEADERS +=
