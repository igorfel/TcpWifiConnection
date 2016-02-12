#-------------------------------------------------
#
# Project created by QtCreator 2016-02-11T17:31:22
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += sensors
QT       += widgets printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TcpWifiConnection
TEMPLATE = app


SOURCES += main.cpp \
    mainwindow.cpp \
    client.cpp \
    server.cpp \
    accelerometerhandler.cpp \
    accelerometerwindow.cpp \
    qcustomplot.cpp

HEADERS  += \
    mainwindow.h \
    client.h \
    server.h \
    accelerometerhandler.h \
    SistemasdeControle/headers/graphicLibs/plot.h \
    SistemasdeControle/src/graphicLibs/plot.hpp \
    accelerometerwindow.h \
    qcustomplot.h

FORMS    += \
    mainwindow.ui \
    accelerometerwindow.ui

CONFIG += mobility
MOBILITY = location

