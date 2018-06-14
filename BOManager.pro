#-------------------------------------------------
#
# Project created by QtCreator 2018-04-11T19:28:50
#
#-------------------------------------------------

QT += core gui charts
QT += sql widgets
QT += xml widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BOManager
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

INCLUDEPATH += $$PWD/src
# INCLUDEPATH += $$PWD/src/plugins/

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/dialog.cpp

HEADERS += \
    src/mainwindow.h \
    src/dialog.h \
    src/database.h

FORMS += \
    src/mainwindow.ui

RESOURCES += \
    src/ressources/icons.qrc \
    masterdetail.qrc
