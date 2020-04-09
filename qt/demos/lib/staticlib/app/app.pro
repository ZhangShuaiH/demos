QT += core
QT -= gui

CONFIG += c++11

TARGET = app
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

unix|win32: LIBS += -L$$PWD/../build-staticlib-unknown-Debug/debug/ -lstaticlib

INCLUDEPATH += $$PWD/../build-staticlib-unknown-Debug/debug
DEPENDPATH += $$PWD/../build-staticlib-unknown-Debug/debug

HEADERS += \
    staticlib.h
