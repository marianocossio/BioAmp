#-------------------------------------------------
#
# Project created by QtCreator 2017-08-02T15:13:12
#
#-------------------------------------------------

QT       += core gui opengl serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BioAmp
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


SOURCES += main.cpp\
    system.cpp \
    acquisitionserver.cpp \
    dataconditioner.cpp \
    filehandler.cpp \
    filter.cpp \
    serverthread.cpp \
    dataset.cpp \
    graph.cpp \
    mainwindow.cpp \
    channellayout.cpp \
    channellayoutadvanced.cpp

HEADERS  += \
    system.h \
    acquisitionserver.h \
    dataconditioner.h \
    filehandler.h \
    filter.h \
    serverthread.h \
    dataset.h \
    graph.h \
    mainwindow.h \
    channellayout.h \
    channellayoutadvanced.h

FORMS    += mainwindow.ui

win32 {
    LIBS += -lOpengl32
}

RC_ICONS = bitmap.ico

RESOURCES += \
    images.qrc
