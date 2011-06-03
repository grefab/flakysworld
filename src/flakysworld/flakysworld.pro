QT += opengl \
	network

INCLUDEPATH += /usr/local/include/Box2D
INCLUDEPATH += ../common
QMAKE_LIBDIR += /usr/local/lib
LIBS += -lBox2D

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
    ../common/interface/variantbinaryconverter.h

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