#-------------------------------------------------
#
# Project created by QtCreator 2013-03-19T11:24:52
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TicTacToeGame
TEMPLATE = app


SOURCES += main.cpp \
    configuregamewidget.cpp \
    mainwindow.cpp \
    mymenu.cpp \
    tictactoewidget.cpp \
    tictactoemodel.cpp \
    savegamewidget.cpp \
    loadgamewidget.cpp \
    tictactoedbdataaccess.cpp \
    tictactoefiledataaccess.cpp

HEADERS  += \
    configuregamewidget.h \
    mainwindow.h \
    mymenu.h \
    tictactoewidget.h \
    tictactoemodel.h \
    savegamewidget.h \
    loadgamewidget.h \
    tictactoedataaccess.h \
    tictactoedbdataaccess.h \
    tictactoefiledataaccess.h

FORMS    +=
