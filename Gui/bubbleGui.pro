#-------------------------------------------------
#
# Project created by QtCreator 2017-12-21T08:35:05
#
#-------------------------------------------------

QT       += core gui

CONFIG += C++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bubbleGui
TEMPLATE = app


SOURCES +=\
        widget.cpp \
    main1.cpp

HEADERS  += widget.h

FORMS    += widget.ui

INCLUDEPATH   += ..\bubbleCalc
