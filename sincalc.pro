#-------------------------------------------------
#
# Project created by QtCreator 2014-04-14T16:20:36
#
#-------------------------------------------------

QT       -= gui

TARGET = sincalc
TEMPLATE = lib

DEFINES += SINCALC_LIBRARY

SOURCES += sincalc.cpp

HEADERS += sincalc.h\
        sincalc_global.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
