#-------------------------------------------------
#
# Project created by QtCreator 2013-07-15T10:07:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = installer
TEMPLATE = app


SOURCES += main.cpp\
        window0.cpp \
    registry.cpp \
    winutils.cpp \
    install.cpp

HEADERS  += window0.h \
    registry.h \
    winutils.h \
    install.h

FORMS    += window0.ui

RESOURCES += \
    installer.qrc

DEFINES += _CRT_SECURE_NO_WARNINGS

LIBS += version.lib
