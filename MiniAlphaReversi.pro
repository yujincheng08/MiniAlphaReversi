#-------------------------------------------------
#
# Project created by QtCreator 2018-03-30T23:31:49
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MiniAlphaReversi
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

INCLUDEPATH += \
                src

SOURCES += \
        src/main.cpp \
        src/view/mainwindow.cpp \
        src/view/piece.cpp \
        src/view/board.cpp \
        src/view/gameview.cpp \
        src/logic/rule.cpp \
    src/ai/minmax.cpp \
    src/ai/mct.cpp \
    src/ai/mcn.cpp \
    src/view/pieces.cpp

HEADERS += \
        src/view/mainwindow.h \
        src/view/piece.h \
        src/view/board.h \
        src/view/gameview.h \
        src/logic/rule.h \
        src/config.h \
    src/logic/position.h \
    src/logic/move.h \
    src/ai/minmax.h \
    src/ai/mct.h \
    src/ai/mcn.h \
    src/view/pieces.h

FORMS +=

OTHER_FILES +=

RESOURCES += \
    assets/image.qrc
