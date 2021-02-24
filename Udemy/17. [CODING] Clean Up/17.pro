TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

CONFIG += static
CONFIG += staticlib

LIBS += -ldl
LIBS += -lGL
LIBS += -lGLEW
LIBS += -lglfw
LIBS += -lGLU
LIBS += -lglut
LIBS += -lm
LIBS += -lrt
LIBS += -lX11
LIBS += -lXcursor
LIBS += -lXi
LIBS += -lXinerama
LIBS += -lXrandr
LIBS += -lXxf86vm
LIBS += -pthread

SOURCES += \
        glwindow.cpp \
        main.cpp \
        mesh.cpp \
        shader.cpp

HEADERS += \
    glwindow.h \
    mesh.h \
    shader.h

DISTFILES += \
    Shaders/shader.frag \
    Shaders/shader.vert \
    Shaders/shader1.frag \
    Shaders/shader1.vert \
    Shaders/shader2.frag \
    Shaders/shader2.vert
