#include <iostream>

#include "cliinterface.hpp"

CliWindow::CliWindow(int argc, char** argv)
{
    this->argc = argc;
    this->argv = argv;

    std::cout << __FILE__ << ":" << __LINE__ << " INTERFACE STUB" << std::endl;
}