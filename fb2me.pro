#-------------------------------------------------
#
# Project created by QtCreator 2014-08-25T19:11:04
#
#-------------------------------------------------

QT       += core gui xml sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fb2me
TEMPLATE = app
VERSION = 0.0.1
DEFINES += VERSIONSTR=\\\"$${VERSION}\\\"

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

RESOURCES += \
    fb2me.qrc

OTHER_FILES += \
    README.md \
    Doxyfile \
    .gitignore

