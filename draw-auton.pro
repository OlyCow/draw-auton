#-------------------------------------------------
#
# Project created by QtCreator 2014-12-23T19:16:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = draw-auton
TEMPLATE = app

SOURCES += main.cpp\
    actionlist.cpp \
    action.cpp \
    actionwidget.cpp \
    actioncustom.cpp \
    actionmove.cpp \
    actiondefine.cpp \
    actiontool.cpp \
    graphicsviewedit.cpp \
    actionturn.cpp \
    definitions.cpp \
    gui/aboutwindow.cpp \
    gui/helpwindow.cpp \
    gui/drawwindow.cpp \
    gui/setupwindow.cpp

HEADERS  += \
    actionlist.h \
    action.h \
    actionwidget.h \
    actioncustom.h \
    actionmove.h \
    actiondefine.h \
    actiontool.h \
    graphicsviewedit.h \
    actionturn.h \
    definitions.h \
    gui/aboutwindow.h \
    gui/setupwindow.h \
    gui/helpwindow.h \
    gui/drawwindow.h

FORMS    += \
    gui/aboutwindow.ui \
    gui/drawwindow.ui \
    gui/helpwindow.ui \
    gui/setupwindow.ui

RESOURCES += \
    icons.qrc \
    fonts.qrc

INCLUDEPATH += \
	$$PWD \
	$$PWD/gui \

QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.6

CONFIG += c++11
