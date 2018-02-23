QT       += core gui
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GoodChat
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
        chatdialog.cpp \
    server.cpp \
    connection.cpp

HEADERS += \
        chatdialog.h \
    server.h \
    connection.h

FORMS += \
        chatdialog.ui
