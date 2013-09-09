QT += opengl \
	network

CONFIG(release, debug|release):QMAKE_CXXFLAGS_RELEASE += -O3

INCLUDEPATH += /usr/local/include
INCLUDEPATH += /usr/local/include/Box2D
INCLUDEPATH += ../common
QMAKE_LIBDIR += /usr/local/lib
LIBS += -lBox2D

QMAKE_CFLAGS_X86_64 += -mmacosx-version-min=10.7
QMAKE_CXXFLAGS_X86_64 = $$QMAKE_CFLAGS_X86_64

HEADERS += \
	interface/connectionmanager.h \
	infrastructure/world.h \
	infrastructure/universe.h \
	infrastructure/engine.h \
	flaky/thruster.h \
	flaky/flaky.h \
	flaky/eye.h \
	bodies/body.h \
	interface/tcpserver.h \
	../common/thing/thing.h \
	../common/interface/persistence.h \
	../common/interface/entityserializer.h \
	../common/external/qjson/src/serializer.h \
	../common/external/qjson/src/parser.h \
	../common/external/qjson/src/json_scanner.h \
	../common/external/qjson/src/json_parser.hh \
	being/sensor.h \
	being/organ.h \
	being/being.h \
	being/actuator.h \
	../common/interface/variantbinaryconverter.h \
	../common/constants.h

SOURCES += \
	main.cpp \
	interface/connectionmanager.cpp \
	infrastructure/world.cpp \
	infrastructure/universe.cpp \
	infrastructure/engine.cpp \
	flaky/thruster.cpp \
	flaky/flaky.cpp \
	flaky/eye.cpp \
	bodies/body.cpp \
	interface/tcpserver.cpp \
	../common/thing/thing.cpp \
	../common/interface/persistence.cpp \
	../common/interface/entityserializer.cpp \
	../common/external/qjson/src/serializer.cpp \
	../common/external/qjson/src/parser.cpp \
	../common/external/qjson/src/json_scanner.cpp \
	../common/external/qjson/src/json_parser.cc \
	being/sensor.cpp \
	being/organ.cpp \
	being/being.cpp \
	being/actuator.cpp \
	../common/interface/variantbinaryconverter.cpp

cache()
