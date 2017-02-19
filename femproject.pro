#-------------------------------------------------
#
# Project created by QtCreator 2016-09-14T18:50:18
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = femproject
TEMPLATE = app

DEFINES += DEBUG=1 USE_INTERFACE=0

QMAKE_CXXFLAGS_DEBUG -= -01
QMAKE_CXXFLAGS_DEBUG -= -02
QMAKE_CXXFLAGS_DEBUG *= -g -O0 -std=c++11 -Wno-deprecated -lGL

QMAKE_CXXFLAGS_RELEASE -= -01
QMAKE_CXXFLAGS_RELEASE -= -02
QMAKE_CXXFLAGS_RELEASE *= -g -O3 -std=c++11 -Wno-deprecated -lGL

unix:!macx {
    LIBS +=  -lGL
}

DEPENDPATH += \
    src/ \
    src/physics \
    src/physics/elements \
    src/physics/loads \
    src/physics/models \
    src/physics/dofs \
    src/interface \
    src/defines \
    src/math \
    src/io \
    src/interface/shaders

INCLUDEPATH += \
    src/ \
    src/defines \
    src/interface \
    src/math \
    src/physics \
    src/physics/elements \
    src/physics/models \
    src/physics/loads \
    src/physics/dofs  \
    src/io

SOURCES += src/interface/main.cpp\
        src/interface/mainwindow.cpp \
    src/physics/dofs/dof.cpp \
    src/physics/dofs/vectordof.cpp \
    src/physics/node.cpp \
    src/physics/element.cpp \
    src/physics/elements/beamelement2d.cpp \
    src/physics/material.cpp \
    src/physics/elements/section.cpp \
    src/physics/load.cpp \
    src/physics/loads/elementload.cpp \
    src/physics/models/model.cpp \
    src/math/coordinatesystem.cpp \
    src/physics/elements/beamelement3d.cpp \
    src/io/input.cpp \
    src/physics/loads/loadcomponent.cpp \
    src/physics/loads/beampontualload.cpp \
    src/physics/loads/beamdistributedload.cpp \
    src/physics/loads/nodeload.cpp \
    src/interface/glwidget.cpp

HEADERS  += src/interface/mainwindow.h \
    src/physics/dofs/dof.h \
    src/physics/dofs/vectordof.h \
    src/physics/dofs/doftype.h \
    src/physics/dofs/restrictiontypes.h \
    src/physics/node.h \
    src/physics/element.h \
    src/physics/elements/beamelement2d.h \
    src/physics/material.h \
    src/physics/elements/section.h \
    src/defines/projectdefines.h \
    src/physics/load.h \
    src/physics/loads/elementload.h \
    src/physics/models/model.h \
    src/math/coordinatesystem.h \
    src/physics/elements/beamelement3d.h \
    src/io/input.h \
    src/physics/loads/loadcomponent.h \
    src/physics/loads/loadtype.h \
    src/physics/loads/beampontualload.h \
    src/physics/loads/beamdistributedload.h \
    src/physics/loads/nodeload.h \
    src/interface/glwidget.h

FORMS    += mainwindow.ui

DISTFILES += \
    src/interface/shaders/vertexshader.vert \
    src/interface/shaders/fragmentshader.frag

RESOURCES += \
    src/resources.qrc
