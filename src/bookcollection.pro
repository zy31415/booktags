#-------------------------------------------------
#
# Project created by QtCreator 2015-07-03T11:23:12
#
#-------------------------------------------------

QT       += core gui xmlpatterns sql xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = src
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    settingsdialog.cpp \
    filescanner.cpp \
    superviseddirectorydialog.cpp \
    programconfigfile.cpp \
    directoryinitializer.cpp

HEADERS  += mainwindow.h \
    settingsdialog.h \
    filescanner.h \
    superviseddirectorydialog.h \
    programconfigfile.h \
    directoryinitializer.h

FORMS    += mainwindow.ui \
    settingsdialog.ui \
    superviseddirectorydialog.ui

DISTFILES +=

RESOURCES += \
    resources.qrc
