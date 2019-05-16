# Neuland

[Deutsch](README_de.md)

a record card questioning system

allows you to to manage record cards and question yourself with them

## Dependencies

- atleast gcc 7
- jsoncpp
- ncurses
- qt5 & qmake (optional)

## Building

### Linux

- install dependencies
- run `make` to compile with Qt5
- run the `cli` target to compile without Qt5

### Compiling for Windows in Linux

- clone the M cross environment (MXE)
- make sure you include the gcc 9 patches
- build qt5 and jsoncpp using `make qt5 jsoncpp`
- run `make CROSS=i686-w64-mingw32.static-` to compile with Qt5
- run the `cli` target to build without Qt5

### Windows

 Compiling on windows is currently unsupported
 If you want to help getting Windows supported help me find a reliable way of compiling this project on Windows
