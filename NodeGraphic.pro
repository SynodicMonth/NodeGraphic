#-------------------------------------------------
#
# Project created by QtCreator 2022-03-26T20:21:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NodeGraphic
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        src/main.cpp \
        src/mainwindow.cpp \
    src/nodescene.cpp \
    src/nodetree.cpp \
    src/nodeview.cpp \
    src/nodeitem.cpp \
    src/nodedata.cpp \
    src/connection.cpp \
    src/port.cpp \
    src/noutput.cpp \
    src/nimage.cpp \
    src/nadd.cpp \
    src/graphsolver.cpp \
    src/ndiff.cpp \
    src/nlut.cpp \
    src/ncontrast.cpp \
    src/nlightness.cpp \
    src/nsaturation.cpp

HEADERS += \
        src/mainwindow.h \
    src/nodescene.h \
    src/nodetree.h \
    src/nodeview.h \
    src/nodeitem.h \
    src/nodedata.h \
    src/connection.h \
    src/port.h \
    src/noutput.h \
    src/nimage.h \
    src/nadd.h \
    src/graphsolver.h \
    src/ndiff.h \
    src/nlut.h \
    src/ncontrast.h \
    src/nlightness.h \
    src/nsaturation.h

FORMS += \
        mainwindow.ui

RESOURCES += \
    tex/textures.qrc
