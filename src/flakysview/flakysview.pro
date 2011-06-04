QT += opengl \
	network

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
    interface/tcpclient.h \
    ../common/interface/variantbinaryconverter.h \
    infrastructure/world.h \
    ../common/constants.h

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
    interface/tcpclient.cpp \
    ../common/interface/variantbinaryconverter.cpp \
    infrastructure/world.cpp

FORMS += \
	gui/surface.ui
