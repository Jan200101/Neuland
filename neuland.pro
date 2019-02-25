#-------------------------------------------------
#
# Project created by QtCreator 2019-02-25T12:40:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Neuland
TEMPLATE = app

OBJECTS_DIR=obj

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += \
        src/main.cpp \
        src/interface.cpp

HEADERS += \
        include/main.hpp \
        include/interface.hpp

FORMS += \
        ui/mainwindow.ui

INCLUDEPATH += \
            src \
            include

# Deployment
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
