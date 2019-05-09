QT             += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET          = Neuland
TEMPLATE        = app

DESTDIR         = ../bin  # bin
OBJECTS_DIR     = obj     # build/obj
MOC_DIR         = moc     # build/moc

DEFINES        += QT_DEPRECATED_WARNINGS

QMAKE_CXXFLAGS += \
               -Wall \
               -Wextra \
               -Wshadow \
               -Wnon-virtual-dtor \
               -pedantic \

CONFIG         += c++11

SOURCES        += \
               src/main.cpp \
               src/qtinterface.cpp \
               src/cliinterface.cpp \
               src/backend/dirs.cpp \

HEADERS        += \
               inc/main.hpp \
               inc/qtinterface.hpp \
               inc/cliinterface.hpp \
               inc/backend/dirs.hpp \
               inc/defines.hpp \

LIBS           += \
               -ljsoncpp \

FORMS          += \
               ui/mainwindow.ui \

RESOURCES      += \
               res/icons.qrc

INCLUDEPATH    += \
               src \
               inc \

# Deployment
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
