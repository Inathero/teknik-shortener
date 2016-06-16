#-------------------------------------------------
#
# Project created by QtCreator 2013-05-03T19:15:18
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = teknik-shortener
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    uploader.cpp

HEADERS  += mainwindow.h \
    uploader.h

FORMS    += mainwindow.ui

RC_FILE = icon.rc

RESOURCES += \
    resource.qrc
