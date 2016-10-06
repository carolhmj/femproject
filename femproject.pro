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

#INCLUDEPATH += ../Eigen/


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/physics/dof.cpp \
    src/physics/vectordof.cpp \
    src/physics/node.cpp \
    src/physics/element.cpp \
    src/physics/beamelement2d.cpp \
    src/physics/material.cpp \
    src/physics/section.cpp

HEADERS  += src/mainwindow.h \
    src/physics/dof.h \
    src/physics/vectordof.h \
    src/physics/doftype.h \
    src/physics/restrictiontypes.h \
    src/physics/node.h \
    src/physics/element.h \
    src/physics/beamelement2d.h \
    src/physics/material.h \
    src/physics/section.h \
    src/projectdefines.h

FORMS    += mainwindow.ui
