#-------------------------------------------------
#
# Project created by QtCreator 2015-07-03T11:23:12
#
#-------------------------------------------------

QT       += core gui xmlpatterns sql xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = booktags
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    settingsdialog.cpp \
    filescanner.cpp \
    programconfigfile.cpp \
    directoryinitializer.cpp \
    currentdirectorydialog.cpp

HEADERS  += mainwindow.h \
    settingsdialog.h \
    filescanner.h \
    programconfigfile.h \
    directoryinitializer.h \
    currentdirectorydialog.h

FORMS    += mainwindow.ui \
    settingsdialog.ui \
    currentdirectorydialog.ui

DISTFILES +=

RESOURCES += \
    resources.qrc
