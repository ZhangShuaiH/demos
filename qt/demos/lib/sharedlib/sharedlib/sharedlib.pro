#-------------------------------------------------
#
# Project created by QtCreator 2018-01-22T15:04:52
#
#-------------------------------------------------

TARGET = sharedlib
TEMPLATE = lib

DEFINES += SHAREDLIB_LIBRARY

SOURCES += sharedlib.cpp

HEADERS += sharedlib.h\
        sharedlib_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
