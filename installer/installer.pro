#-------------------------------------------------
#
# Project created by QtCreator 2013-07-15T10:07:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = installer
TEMPLATE = app

RC_FILE = installer.rc

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
    storm.h \
    winutils.h \
    bnftp.h

FORMS    += window0.ui

RESOURCES += \
    installer.qrc


CONFIG += static
CONFIG(debug, debug|release){
    DESTDIR = $$PWD/../Debug
    OBJECTS_DIR = $$PWD/../Debug
    MOC_DIR = $$PWD/../Debug
}

CONFIG(release, debug|release){
    DESTDIR = $$PWD/../Release
    OBJECTS_DIR = $$PWD/../Release
    MOC_DIR = $$PWD/../Release
}

DEFINES += _CRT_SECURE_NO_WARNINGS

LIBS += version.lib

win32: LIBS += -L$$PWD/ -lStormLib

INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/

win32: PRE_TARGETDEPS += $$PWD/StormLib.lib

#CONFIG -= embed_manifest_exe

#QMAKE_POST_LINK += upx.exe ../Release-static/release/installer.exe
