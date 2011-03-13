QT += opengl \
	network

SOURCES += src/main.cpp \
	src/bodies/body.cpp \
	src/infrastructure/engine.cpp \
	src/bodies/circlebody.cpp \
	src/gui/bodyviews/bodyview.cpp \
	src/gui/bodyviews/circlebodyview.cpp \
	src/bodies/polygonbody.cpp \
	src/gui/bodyviews/polygonbodyview.cpp \
	src/bodycontroller.cpp \
	src/flaky/flaky.cpp \
	src/infrastructure/world.cpp \
	src/gui/graphicsview.cpp \
	src/infrastructure/universe.cpp \
	src/gui/surface.cpp \
	src/flaky/eye.cpp \
	src/gui/flakyviews/eyeview.cpp \
	src/being/sensor.cpp \
	src/interface/neuronserializer.cpp \
	src/external/qjson/src/serializer.cpp \
	src/external/qjson/src/parser.cpp \
	src/external/qjson/src/json_scanner.cpp \
	src/external/qjson/src/json_parser.cc \
	src/interface/tcpserver.cpp \
	src/being/organ.cpp \
	src/being/actuator.cpp \
	src/being/being.cpp

INCLUDEPATH += /usr/local/include/Box2D
INCLUDEPATH += src
LIBPATH += /usr/local/lib
LIBS += -lBox2D

HEADERS += \
	src/bodies/body.h \
	src/infrastructure/engine.h \
	src/bodies/circlebody.h \
	src/gui/bodyviews/bodyview.h \
	src/gui/bodyviews/circlebodyview.h \
	src/bodies/polygonbody.h \
	src/gui/bodyviews/polygonbodyview.h \
	src/bodycontroller.h \
	src/flaky/flaky.h \
	src/infrastructure/world.h \
	src/gui/graphicsview.h \
	src/infrastructure/universe.h \
	src/gui/surface.h \
	src/flaky/eye.h \
	src/gui/flakyviews/eyeview.h \
	src/being/sensor.h \
	src/external/qjson/src/parser.h \
	src/external/qjson/src/json_scanner.h \
	src/external/qjson/src/json_parser.hh \
	src/external/qjson/src/serializer.h \
	src/interface/neuronserializer.h \
	src/interface/tcpserver.h \
	src/being/organ.h \
	src/being/actuator.h \
	src/being/being.h

FORMS += \
	src/gui/surface.ui
