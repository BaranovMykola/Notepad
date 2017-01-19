#-------------------------------------------------
#
# Project created by QtCreator 2017-01-10T19:13:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Notepad
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    undefinedfilestate.cpp \
    savedfilestate.cpp \
    unsavedfilestate.cpp \
    abstractsavefilestate.cpp \
    savedialog.cpp \
    savefilefunction.cpp \
    finddialog.cpp \
    replacedialog.cpp \
    gotodialog.cpp \
    fontdialog.cpp \
    fontmodel.cpp

HEADERS  += mainwindow.h \
    undefinedfilestate.h \
    savedfilestate.h \
    unsavedfilestate.h \
    abstractsavefilestate.h \
    savedialog.h \
    savefilefunction.h \
    constants.h \
    finddialog.h \
    replacedialog.h \
    gotodialog.h \
    fontdialog.h \
    fontmodel.h

FORMS    += mainwindow.ui \
    savedialog.ui \
    finddialog.ui \
    replacedialog.ui \
    gotodialog.ui \
    fontdialog.ui

CONFIG += c++14
