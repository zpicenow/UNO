#-------------------------------------------------
#
# Project created by QtCreator 2017-07-18T17:01:40
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = uno
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        index.cpp \
    card.cpp \
    cardlist.cpp \
    cardpicture.cpp \
    gameover.cpp \
    gameprocess.cpp \
    hand.cpp \
    helptext.cpp \
    maininterface.cpp \
    method.cpp \
    player.cpp \
    rebot.cpp \
    userplayer.cpp

HEADERS += \
        index.h \
    card.h \
    cardlist.h \
    cardpicture.h \
    gameover.h \
    gameprocess.h \
    hand.h \
    helptext.h \
    maininterface.h \
    method.h \
    player.h \
    rebot.h \
    userplayer.h

FORMS += \
        index.ui \
    cardlist.ui \
    gameover.ui \
    helptext.ui \
    maininterface.ui

RESOURCES += \
    img.qrc
