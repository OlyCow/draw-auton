# Project created by QtCreator: 2014-12-23 19:16:05



QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = draw-auton
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
    actionlist.cpp \
    graphicsviewedit.cpp \
    definitions.cpp \
    gui/aboutwindow.cpp \
    gui/helpwindow.cpp \
    gui/drawwindow.cpp \
    gui/setupwindow.cpp \
    action/action.cpp \
    action/actioncustom.cpp \
    action/actionmove.cpp \
    action/actiontool.cpp \
    action/actionturn.cpp \
    action/actionwidget.cpp \
    action/actiondefine.cpp

HEADERS  += \
    actionlist.h \
    graphicsviewedit.h \
    definitions.h \
    gui/aboutwindow.h \
    gui/setupwindow.h \
    gui/helpwindow.h \
    gui/drawwindow.h \
    action/action.h \
    action/actioncustom.h \
    action/actionmove.h \
    action/actiontool.h \
    action/actionturn.h \
    action/actionwidget.h \
    action/actiondefine.h

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
	$$PWD/action \
	$$PWD/gui \

QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.6
