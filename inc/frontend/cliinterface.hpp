#ifndef CLIINTERFACE_HPP
#define CLIINTERFACE_HPP

/* 
 * You can't include NCurses here with QT present
 */

/**
 * @brief class for the ncurses interface
 */
class CliWindow
{
   private:
    int argc;
    char** argv;

   public:
    CliWindow(int argc, char** argv);

    int exec();
};

#endif