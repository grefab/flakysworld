#-------------------------------------------------
#
# Project created by QtCreator 2011-03-24T22:42:14
#
#-------------------------------------------------

QT       += core gui widgets network

TARGET = flakysremote
TEMPLATE = app

CONFIG(release, debug|release):QMAKE_CXXFLAGS_RELEASE += -O3
CONFIG += c++11

SOURCES += main.cpp\
        surface.cpp \
    client.cpp

HEADERS  += surface.h \
    client.h

FORMS    += surface.ui

cache()
