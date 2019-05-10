#include <iostream>

#include "cliinterface.hpp"

CliWindow::CliWindow(int argc, char** argv)
{
    this->argc = argc;
    this->argv = argv;
}

int CliWindow::exec()
{
    std::cout << __FILE__ << ":" << __LINE__ << " INTERFACE STUB" << std::endl;

    return 0;
}