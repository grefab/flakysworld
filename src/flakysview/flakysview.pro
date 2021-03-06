QT += opengl network widgets

CONFIG(release, debug|release):QMAKE_CXXFLAGS_RELEASE += -O3

QMAKE_CFLAGS_X86_64 += -mmacosx-version-min=10.7
QMAKE_CXXFLAGS_X86_64 = $$QMAKE_CFLAGS_X86_64

INCLUDEPATH += ../common

HEADERS += \
    gui/views/thingview.h \
    gui/surface.h \
    gui/graphicsview.h \
    ../common/thing/thing.h \
    ../common/interface/persistence.h \
    ../common/interface/entityserializer.h \
    ../common/external/qjson/src/serializer.h \
    ../common/external/qjson/src/parser.h \
    ../common/external/qjson/src/json_scanner.h \
    ../common/external/qjson/src/json_parser.hh \
    ../common/interface/tcpclient.h \
    ../common/interface/variantbinaryconverter.h \
    infrastructure/world.h \
    ../common/constants.h \
    infrastructure/viewmanager.h \
    gui/views/eyeview.h \
    gui/views/actuatorview.h \
    ../common/interface/universeclient.h

SOURCES += \
    main.cpp \
    gui/views/thingview.cpp \
    gui/surface.cpp \
    gui/graphicsview.cpp \
    ../common/thing/thing.cpp \
    ../common/interface/persistence.cpp \
    ../common/interface/entityserializer.cpp \
    ../common/external/qjson/src/serializer.cpp \
    ../common/external/qjson/src/parser.cpp \
    ../common/external/qjson/src/json_scanner.cpp \
    ../common/external/qjson/src/json_parser.cc \
    ../common/interface/tcpclient.cpp \
    ../common/interface/variantbinaryconverter.cpp \
    infrastructure/world.cpp \
    infrastructure/viewmanager.cpp \
    gui/views/eyeview.cpp \
    gui/views/actuatorview.cpp \
    ../common/interface/universeclient.cpp

FORMS += \
    gui/surface.ui

cache()
