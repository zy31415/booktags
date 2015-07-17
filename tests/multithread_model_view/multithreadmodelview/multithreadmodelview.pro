#-------------------------------------------------
#
# Project created by QtCreator 2015-07-16T18:07:08
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = multithreadmodelview
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tablemodel.cpp

HEADERS  += mainwindow.h \
    tablemodel.h

FORMS    += mainwindow.ui
