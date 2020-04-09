#-------------------------------------------------
#
# Project created by QtCreator 2018-01-22T16:35:28
#
#-------------------------------------------------

QT       -= gui

TARGET = staticlib
TEMPLATE = lib
CONFIG += staticlib

SOURCES += staticlib.cpp

HEADERS += staticlib.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

