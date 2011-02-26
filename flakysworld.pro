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
    sensor.cpp
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
    sensor.h

FORMS += \
    surface.ui
