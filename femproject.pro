#-------------------------------------------------
#
# Project created by QtCreator 2016-09-14T18:50:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = femproject
TEMPLATE = app

DEFINES += DEBUG=1 USE_INTERFACE=0

DEBUG : {
    QMAKE_CXXFLAGS += -std=c++11 -Wno-deprecated
}
!DEBUG : {
    QMAKE_CXXFLAGS += -std=c++11 -Wno-deprecated -O3
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
    src/math

INCLUDEPATH += \
    src/ \
    src/defines \
    src/interface \
    src/math \
    src/physics \
    src/physics/elements \
    src/physics/models \
    src/physics/loads \
    src/physics/dofs

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
    src/physics/loads/nodeload.cpp \
    src/physics/loads/elementload.cpp \
    src/physics/loads/pontualload2dbeam.cpp \
    src/physics/loads/distributedload2dbeam.cpp \
    src/physics/loads/distributedhorizontalload2dbeam.cpp \
    src/physics/models/model.cpp \
    src/physics/loads/dofload.cpp \
    src/physics/loads/vectordofload.cpp \
    src/math/coordinatesystem.cpp

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
    src/physics/loads/pontualload2dbeam.h \
    src/physics/loads/distributedverticalload2dbeam.h \
    src/physics/loads/distributedhorizontalload2dbeam.h \
    src/physics/models/model.h \
    src/physics/loads/dofload.h \
    src/physics/loads/vectordofload.h \
    src/math/coordinatesystem.h

FORMS    += mainwindow.ui
