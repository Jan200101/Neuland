# Neuland

a record card questioning system

allows you to to manage record cards and question yourself with them

## Dependencies
 - jsoncpp
 - Qt5 & qmake (optional)

## Building

### Linux:
 - install dependencies
 - run `make`

### Cross compiling for Windows
 - clone the M cross environment (MXE)
 - build qt5 and jsoncpp using `make qt5 jsoncpp`
 - run `make CROSS=i686-w64-mingw32.static-`
