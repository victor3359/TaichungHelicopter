#-------------------------------------------------
#
# Project created by QtCreator 2017-07-11T11:10:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Taichung_Helicopter
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    page_def.cpp

HEADERS  += mainwindow.h \
    keybroad_def.h \
    keybroad_scan.h \
    page_def.h

FORMS    += mainwindow.ui

LIBS += -L/usr/local/include -lwiringPi

LIBS += -L/usr/local/include -lcrypt
