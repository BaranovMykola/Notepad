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
    savedfilestate.cpp \
    unsavedfilestate.cpp \
    abstractsavefilestate.cpp \
    savedialog.cpp \
    savefilefunction.cpp \
    finddialog.cpp \
    replacedialog.cpp \
    gotodialog.cpp \
    fontdialog.cpp \
    loadingdialog.cpp \
    aboutdialog.cpp \
    mementoqplaintextedit.cpp \
    caretakerqplainttextedit.cpp

HEADERS  += mainwindow.h \
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
    loadingdialog.h \
    aboutdialog.h \
    mementoqplaintextedit.h \
    caretakerqplainttextedit.h

FORMS    += mainwindow.ui \
    savedialog.ui \
    finddialog.ui \
    gotodialog.ui \
    fontdialog.ui \
    loadingdialog.ui \
    aboutdialog.ui \
    replacedialog.ui

CONFIG += c++14

RC_ICONS += Notepad.ico
