#-------------------------------------------------
#
# Project created by QtCreator 2018-09-10T02:40:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = demoGame
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    Background.cpp \
    EventEmitter.cpp \
    FramesDataPool.cpp \
    Game.cpp \
    globalconst.cpp \
    GraphicsView.cpp \
    Player.cpp \
    Sprite.cpp \
    Ticker.cpp \
    libs/tweeny/tween.tcc \
    libs/tweeny/tweenone.tcc \
    libs/tweeny/tweenpoint.tcc \
    libs/tweeny/tweeny.tcc \
    Shark.cpp \
    EntitiesManager.cpp

HEADERS += \
    Background.h \
    EventEmitter.h \
    FramesDataPool.h \
    Game.h \
    globalconst.h \
    GraphicsView.h \
    Player.h \
    Sprite.h \
    Ticker.h \
    libs/tweeny/dispatcher.h \
    libs/tweeny/easing.h \
    libs/tweeny/easingresolve.h \
    libs/tweeny/int2type.h \
    libs/tweeny/tween.h \
    libs/tweeny/tweenpoint.h \
    libs/tweeny/tweentraits.h \
    libs/tweeny/tweeny.h \
    Shark.h \
    EntitiesManager.h


CONFIG += mobility
MOBILITY = 

SUBDIRS += \
    demoGame.pro

ANDROID_PACKAGE_SOURCE_DIR = $${PWD}/android-sources
