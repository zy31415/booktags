#-------------------------------------------------
#
# Project created by QtCreator 2015-07-16T19:58:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = multithreadmodelview
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tagslist.cpp \
    addstringthread.cpp

HEADERS  += mainwindow.h \
    tagslist.h \
    addstringthread.h

FORMS    += mainwindow.ui
