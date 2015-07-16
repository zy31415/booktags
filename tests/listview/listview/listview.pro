#-------------------------------------------------
#
# Project created by QtCreator 2015-07-13T18:05:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = listview
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    stringlist.cpp \
    rightclickedmenu.cpp

HEADERS  += mainwindow.h \
    stringlist.h \
    rightclickedmenu.h

FORMS    += mainwindow.ui
