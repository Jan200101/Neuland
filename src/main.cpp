#include <QApplication>
#include "interface.hpp"

#ifdef UNIT_TEST
#include "catch2/catch.hpp"
#endif

#ifndef UNIT_TEST
int main(int argc, char** argv)
{
    QApplication App(argc, argv);
    MainWindow window;
    window.show();

    return App.exec();
}
#endif
