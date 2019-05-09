#include <cstring>
#include <iostream>

#include "qtinterface.hpp"

#ifndef NO_QT
#include <QApplication>

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
    std::cout << __FILE__ << ":" << __LINE__ << " INTERFACE STUB" << std::endl;
    return 0;
}

int main(int argc, char** argv)
{
    // assign a standard function to call for the app for later reassignment
    int (*app)(int&, char**) = rungraphical;

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
            else if (!std::strcmp(argv[i], "--grapical"))
            {
                app = rungraphical;
            }
            else if (!std::strcmp(argv[i], "--cli"))
            {
                app = runcli;
            }
        }
        if (terminate)
            return 0;
    }

    return app(argc, argv);
}
