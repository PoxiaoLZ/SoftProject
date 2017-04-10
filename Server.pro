#-------------------------------------------------
#
# Project created by QtCreator 2017-04-10T10:59:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Server
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    aircondition.cpp \
    roomstate.cpp

HEADERS  += mainwindow.h \
    aircondition.h \
    roomstate.h

FORMS    += mainwindow.ui
