QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Neuland
TEMPLATE = app

DESTDIR = ../bin
OBJECTS_DIR = obj
MOC_DIR = moc

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += \
        src/main.cpp \
        src/interface.cpp

HEADERS += \
        inc/main.hpp \
        inc/interface.hpp

FORMS += \
        ui/mainwindow.ui

RESOURCES += \
        res/icons.qrc

INCLUDEPATH += \
        src \
        inc \

# Deployment
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
