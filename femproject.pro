#-------------------------------------------------
#
# Project created by QtCreator 2016-09-14T18:50:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = femproject
TEMPLATE = app

DEFINES += DEBUG=1

DEBUG : {
    QMAKE_CXXFLAGS += -std=c++11
}
!DEBUG : {
    QMAKE_CXXFLAGS += -std=c++11 -O3
}

INCLUDEPATH += -isystem ../inc/Eigen/


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/physics/dof.cpp \
    src/physics/vectordof.cpp \
    src/physics/node.cpp \
    src/physics/element.cpp

HEADERS  += src/mainwindow.h \
    src/physics/dof.h \
    src/physics/vectordof.h \
    src/physics/doftype.h \
    src/physics/restrictiontypes.h \
    src/physics/node.h \
    src/physics/element.h

FORMS    += mainwindow.ui
