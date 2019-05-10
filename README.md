# Neuland

a record card questioning system

allows you to to manage record cards and question yourself with them

## Dependencies
 - jsoncpp
 - ncurses
 - qt5 & qmake (optional)

## Building

### Linux:
 - install dependencies
 - run `make` to compile with Qt5
 - run the `cli` target to compile without Qt5

### Cross compiling for Windows
 - clone the M cross environment (MXE)
 - build qt5 and jsoncpp using `make qt5 jsoncpp`
 - run `make CROSS=i686-w64-mingw32.static-` to compile with Qt5
 - run the `cli` target to build without Qt5
