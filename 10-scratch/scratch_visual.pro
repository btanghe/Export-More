#-------------------------------------------------
#
# Project created by QtCreator 2015-09-21T14:47:59
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
#KIT = Desktop
#KIT = RPI

TARGET = scratch_visual
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

#gcc -o gpio -I ../../src ../../src/bcm2835.c gpio.c
contains( KIT, RPI ) {
    SOURCES += ../../src/bcm2835.c
    INCLUDEPATH += ../../src

}

RESOURCES += \
    leds.qrc
