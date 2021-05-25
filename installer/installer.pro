#-------------------------------------------------
#
# Project created by QtCreator 2013-07-15T10:07:50
#
#-------------------------------------------------

QT += core gui widgets

TARGET = installer
TEMPLATE = app

RC_FILE = installer.rc

QMAKE_LFLAGS_WINDOWS = /SUBSYSTEM:WINDOWS,5.01
#DEFINES += _ATL_XP_TARGETING

SOURCES += main.cpp\
        window0.cpp \
    registry.cpp \
    install.cpp \
    mpq.cpp \
    config.cpp \
    bnftp.cpp


HEADERS  += window0.h \
    registry.h \
    winutils.h \
    install.h \
    config.h \
    mpq.h \
    util.h \
    winutils.h \
    bnftp.h

FORMS += window0.ui

RESOURCES += \
    installer.qrc \
    installer2.qrc \
    installer3.qrc

CONFIG += static
CONFIG += resources_big

DEFINES += _CRT_SECURE_NO_WARNINGS
DEFINES += _UNICODE
DEFINES += UNICODE

LIBS += version.lib
LIBS += msvcrt.lib

## STORMLIB
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/stormlib/ -lstorm

INCLUDEPATH += $$PWD/stormlib
DEPENDPATH += $$PWD/stormlib

# Fix for UI changes not taking effect
UI_DIR = $$PWD

## Manifest
win32 {
    CONFIG += embed_manifest_exe
    QMAKE_LFLAGS_WINDOWS += /MANIFESTUAC:level=\'requireAdministrator\'
}

Release:QMAKE_CXXFLAGS += /MT
Debug:QMAKE_CXXFLAGS += /MTd
Release: QMAKE_LIBFLAGS += /NODEFAULTLIB:LIBCMT
