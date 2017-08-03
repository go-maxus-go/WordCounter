include(../defaults.pri)

CONFIG += console c++11 c++14
CONFIG -= app_bundle
CONFIG -= qt

TEMPLATE = app

SOURCES += main.cpp

LIBS += -L../src -lWordCounter
