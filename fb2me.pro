#-------------------------------------------------
#
# Project created by QtCreator 2014-08-25T19:11:04
#
#-------------------------------------------------

QT       += core gui xml sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fb2me
TEMPLATE = app
VERSION = 0.1.0
DEFINES += VERSIONSTR=\\\"$${VERSION}\\\"

SOURCES += src/main.cpp\
    src/mainwindow.cpp \
    src/tablemodel.cpp \
    src/fb2record.cpp \
    src/person.cpp \
    src/reader.cpp

HEADERS  += src/mainwindow.h \
    src/tablemodel.h \
    src/fb2record.h \
    src/person.h \
    src/reader.h

# 3rd party components
HEADERS += 3rdparty/miniz.h
SOURCES += 3rdparty/miniz.c

RESOURCES += \
    res/fb2me.qrc

OTHER_FILES += \
    README.md \
    Doxyfile \
    .gitignore

