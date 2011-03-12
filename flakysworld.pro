QT += opengl \
	network

SOURCES += main.cpp \
	body.cpp \
	engine.cpp \
	circlebody.cpp \
	bodyview.cpp \
	circlebodyview.cpp \
	polygonbody.cpp \
	polygonbodyview.cpp \
	bodycontroller.cpp \
	flaky.cpp \
	world.cpp \
	graphicsview.cpp \
	universe.cpp \
	surface.cpp \
	eye.cpp \
	eyeview.cpp \
	sensor.cpp \
	neuronserializer.cpp \
	qjson/src/serializer.cpp \
	qjson/src/parser.cpp \
	qjson/src/json_scanner.cpp \
	qjson/src/json_parser.cc \
	tcpserver.cpp \
	organ.cpp \
	actuator.cpp \
	being.cpp

INCLUDEPATH += /usr/local/include/Box2D
LIBPATH += /usr/local/lib
LIBS += -lBox2D

HEADERS += \
	body.h \
	engine.h \
	circlebody.h \
	bodyview.h \
	circlebodyview.h \
	polygonbody.h \
	polygonbodyview.h \
	bodycontroller.h \
	flaky.h \
	world.h \
	graphicsview.h \
	universe.h \
	surface.h \
	eye.h \
	eyeview.h \
	sensor.h \
	qjson/src/parser.h \
	qjson/src/json_scanner.h \
	qjson/src/json_parser.hh \
	qjson/src/serializer.h \
	neuronserializer.h \
	tcpserver.h \
	organ.h \
	actuator.h \
	being.h

FORMS += \
	surface.ui
