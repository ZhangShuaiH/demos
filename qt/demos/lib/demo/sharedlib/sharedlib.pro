#-------------------------------------------------
#
# Project created by QtCreator 2018-01-22T17:46:52
#
#-------------------------------------------------


TARGET = sharedlib
TEMPLATE = lib

DEFINES += SHAREDLIB_LIBRARY

SOURCES += sharedlib.cpp \
    myclass.cpp

HEADERS += sharedlib.h\
        sharedlib_global.h \
    myclass.h \
    imyclass.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
