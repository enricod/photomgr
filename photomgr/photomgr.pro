#-------------------------------------------------
#
# Project created by QtCreator 2018-03-23T16:17:17
#
#-------------------------------------------------

QT       += core gui  concurrent widgets
QMAKE_CXXFLAGS += -std=c++0x

LIBS += -L/usr/local/lib -lraw

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = photomgr
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    thumbsworker.cpp

HEADERS  += mainwindow.h \
    thumbsworker.h

FORMS    += mainwindow.ui

DISTFILES += \
    README.md
