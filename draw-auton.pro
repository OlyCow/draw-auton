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
        drawwindow.cpp \
    actionlist.cpp \
    action.cpp \
    setupwindow.cpp \
    aboutwindow.cpp \
    helpwindow.cpp \
    actionwidget.cpp \
    actioncustom.cpp \
    actionmove.cpp \
    actiondefine.cpp \
    actiontool.cpp \
    graphicsviewedit.cpp \
    actionturn.cpp

HEADERS  += drawwindow.h \
    actionlist.h \
    action.h \
    setupwindow.h \
    aboutwindow.h \
    helpwindow.h \
    actionwidget.h \
    actioncustom.h \
    actionmove.h \
    actiondefine.h \
    actiontool.h \
    graphicsviewedit.h \
    actionturn.h

FORMS    += drawwindow.ui \
    setupwindow.ui \
    aboutwindow.ui \
    helpwindow.ui

RESOURCES += \
    icons.qrc \
    fonts.qrc

QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.6
