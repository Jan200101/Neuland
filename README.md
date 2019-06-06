# Neuland

english [Deutsch](README_de.md)

a record card questioning system

allows you to to manage record cards and question yourself with them

## Dependencies

- atleast gcc 7 (gcc 9 for compiling for Windows[1])
- jsoncpp
- ncurses
- qt5 & qmake (optional)

## Building

### Linux

- install dependencies
- run `make` to compile
- run the `qt` target to compile with Qt5

### Compiling for Windows in Linux

- clone the M cross environment (MXE)
- make sure you include the gcc 9 patches
- build qt5, ncurses and jsoncpp using `make qt5 ncurses jsoncpp ncurses`
- run `make CROSS=i686-w64-mingw32.static-` to compile
- run the `qt` target to build with Qt5

### Windows

 Compiling on windows is currently unsupported
 If someone knows how to compile a Qt5 application on Windows you can open an issue with a guide



[1] gcc 9 includes the patches to make std::filesystem work on Windows machines
