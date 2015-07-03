#-------------------------------------------------
#
# Project created by QtCreator 2015-07-03T11:23:12
#
#-------------------------------------------------

QT       += core gui xmlpatterns sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bookcollection
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    settingsdialog.cpp \
    programinitializer.cpp \
    filescanner.cpp

HEADERS  += mainwindow.h \
    settingsdialog.h \
    programinitializer.h \
    filescanner.h

FORMS    += mainwindow.ui \
    settingsdialog.ui

DISTFILES +=

RESOURCES += \
    resources.qrc
