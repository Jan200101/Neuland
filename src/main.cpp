#include <cstring>
#include <iostream>
#include <string>

#include "cliinterface.hpp"

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
#include "qtinterface.hpp"

int rungraphical(int& argc, char** argv)
{
    QApplication App(argc, argv);
    MainWindow window;
    window.show();

    return App.exec();
}
#endif

/**
 * STUB CLI interface function
 */
int runcli(int& argc, char** argv)
{
    /**
     * \todo implement interface
     */

    CliWindow window(argc, argv);

    // return window.show()
    return 0;
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
            /**
             * \todo add useful cli arguments
             */
            if (!std::strcmp(argv[i], "--help"))
            {
                std::cerr << "Usage: " << argv[0] << " [--graphical|--cli]"
                                                     "\nOptions:"
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
            else if (!std::strcmp(argv[i], "--config"))
            {
                Json::Value k = config::readConfig(
                    backend::getConfigdir(backend::getHomedir()) + "/config.json");

                if (!k.empty())
                    std::cout << k << std::endl;
            }
        }
        if (terminate)
            return 0;
    }

    return app(argc, argv);
}
