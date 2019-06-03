QT             += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET          = Neuland
TEMPLATE        = app

# directories relative to the build direcotry
# the main makefile handles the build directory for you
DESTDIR         = ../bin  # bin
OBJECTS_DIR     = obj     # build/obj
MOC_DIR         = moc     # build/moc

DEFINES        += QT_DEPRECATED_WARNINGS

*-g++ {
  GCC_VERSION = $$system("$${QMAKE_CXX} -dumpversion")
  contains(GCC_VERSION, 9(.[0-9]|)+) {
    CONFIG += g++9
  }
}

QMAKE_CXXFLAGS += \
               -Wall \
               -Wextra \
               -pedantic \
               -Winit-self \
               -Wcast-align \
               -Wuninitialized \
               -Wpointer-arith \
               -Wunreachable-code \

CONFIG         += c++1z

SOURCES        += \
               src/main.cpp \
               src/frontend/qtinterface.cpp \
               src/frontend/cliinterface.cpp \
               src/backend/config.cpp \
               src/backend/files.cpp \
               src/backend/dirs.cpp \

HEADERS        += \
               inc/main.hpp \
               inc/defines.hpp \
               inc/frontend/qtinterface.hpp \
               inc/frontend/cliinterface.hpp \
               inc/backend/config.hpp \
               inc/backend/files.hpp \
               inc/backend/dirs.hpp \

LIBS           += \
               -ljsoncpp \
               -lncurses \


# gcc 9 doesn't need you to and can't link the filesystem library
!g++9: LIBS   +=
               -lstdc++fs \

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
