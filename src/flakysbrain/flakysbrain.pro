#-------------------------------------------------
#
# Project created by QtCreator 2013-09-10T01:56:38
#
#-------------------------------------------------

QT       += core network widgets

QMAKE_CFLAGS_X86_64 += -mmacosx-version-min=10.7
QMAKE_CXXFLAGS_X86_64 = $$QMAKE_CFLAGS_X86_64

TARGET = flakysbrain
TEMPLATE = app

CONFIG(release, debug|release):QMAKE_CXXFLAGS_RELEASE += -O3
CONFIG += console
CONFIG -= app_bundle
CONFIG += c++11

INCLUDEPATH += ../common


HEADERS += \
    ../common/thing/thing.h \
    ../common/interface/persistence.h \
    ../common/interface/entityserializer.h \
    ../common/external/qjson/src/serializer.h \
    ../common/external/qjson/src/parser.h \
    ../common/external/qjson/src/json_scanner.h \
    ../common/external/qjson/src/json_parser.hh \
    ../common/interface/tcpclient.h \
    ../common/interface/variantbinaryconverter.h \
    ../common/constants.h \
    ../common/interface/universeclient.h \
    infrastructure/brain.h \
    actionobjects/actionobject.h \
    actionobjects/neuron.h \
    controllers/engine.h \
    gui/surface.h \
    helpers/id.h \
    helpers/message.h \
    helpers/timer.h


SOURCES += \
    main.cpp \
    ../common/thing/thing.cpp \
    ../common/interface/persistence.cpp \
    ../common/interface/entityserializer.cpp \
    ../common/external/qjson/src/serializer.cpp \
    ../common/external/qjson/src/parser.cpp \
    ../common/external/qjson/src/json_scanner.cpp \
    ../common/external/qjson/src/json_parser.cc \
    ../common/interface/tcpclient.cpp \
    ../common/interface/variantbinaryconverter.cpp \
    ../common/interface/universeclient.cpp \
    infrastructure/brain.cpp \
    actionobjects/actionobject.cpp \
    actionobjects/neuron.cpp \
    controllers/engine.cpp \
    gui/surface.cpp \
    helpers/id.cpp \
    helpers/message.cpp \
    helpers/timer.cpp

cache()

OTHER_FILES += \
    ../common/messaging/brainmodels.proto

FORMS += \
    gui/surface.ui
