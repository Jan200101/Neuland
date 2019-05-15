#include <cstring>
#include <iostream>
#include <string>

#include "frontend/cliinterface.hpp"

#include "defines.hpp"

#include "backend/config.hpp"
#include "backend/dirs.hpp"

#ifndef NO_QT
#define DEFAULTINTERFACE rungraphical
#else
#define DEFAULTINTERFACE runcli
#endif

#ifndef NO_QT
#include <QApplication>
#include "frontend/qtinterface.hpp"

/**
 * @brief function that initializes and executes the graphical (Qt5) interface
 */
int rungraphical(int& argc, char** argv)
{
    QApplication App(argc, argv);
    MainWindow window;
    window.show();

    return App.exec();
}
#endif

/**
 * @brief function that initializes and executes the commandline (ncurses) interface
 */
int runcli(int& argc, char** argv)
{
    CliWindow window(argc, argv);

    return window.exec();
}

int main(int argc, char** argv)
{
    // assign a standard function to call for the app for later reassignment
    int (*app)(int&, char**) = DEFAULTINTERFACE;

    if (argc > 1)
    {
        bool terminate = false;
        for (int i = 1; i < argc; ++i)
        {
            if (!std::strcmp(argv[i], "--help"))
            {
                std::cerr << "Usage: " << argv[0]
                          << "\nOptions:"
                             "\n  --help                     Shows this message"
#ifndef NO_QT
                             "\n  --graphical                Uses a graphical interface"
#endif
                             "\n  --cli                      Uses a CLI interface"
                          << std::endl;

                terminate = true;
            }
#ifndef NO_QT
            else if (!std::strcmp(argv[i], "--grapical"))
            {
                app = rungraphical;
            }
#endif
            else if (!std::strcmp(argv[i], "--cli"))
            {
                app = runcli;
            }
            // \TODO remove
            else if (!std::strcmp(argv[i], "--config"))
            {
                Backend::makeConfigdir();

                std::string cfgfile = Backend::getConfigdir(Backend::getHomedir()) + "/config.json";
                std::cout << cfgfile << std::endl;
                Json::Value k = Config::readConfig(cfgfile);

                std::cout << k << std::endl;
            }
            // \TODO remove
            else if (!std::strcmp(argv[i], "--norun"))
            {
                terminate = true;
            }
        }
        if (terminate)
            return 0;
    }

    return app(argc, argv);
}
