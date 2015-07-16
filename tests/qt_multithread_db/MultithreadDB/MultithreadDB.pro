#-------------------------------------------------
#
# Project created by QtCreator 2015-07-10T16:58:23
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MultithreadDB
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    database.cpp \
    updatethread.cpp

HEADERS  += mainwindow.h \
    database.h \
    utils.h \
    updatethread.h

FORMS    += mainwindow.ui
