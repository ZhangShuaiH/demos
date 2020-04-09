#-------------------------------------------------
#
# Project created by QtCreator 2018-01-22T16:01:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = app2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    sharedlib.h \
    sharedlib_global.h

FORMS    += mainwindow.ui

unix|win32: LIBS += -L$$PWD/../build-sharedlib-unknown-Debug/debug/ -lsharedlib

INCLUDEPATH += $$PWD/../build-sharedlib-unknown-Debug/debug
DEPENDPATH += $$PWD/../build-sharedlib-unknown-Debug/debug
